/*
 * Copyright (C) 2025  Pedro Bianchini de Quadros
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef READARFFFILE_H
#define READARFFFILE_H

#include "../types.h"
#include "../instances/instance.h"

class ReadArffFile {
private:
    String name_file_;
    IFStream file_;
    Vec<String> attributes_;
    bool inData_ = false;

    ValueType parseToken(const std::string& token) {
        auto t = token;
        {
            long val;
            auto [ptr, ec] = std::from_chars(t.data(), t.data() + t.size(), val);
            if (ec == std::errc() && ptr == t.data() + t.size()) {
                return val;
            }
        }

        try {
            size_t idx;
            double d = std::stod(t, &idx);
            if (idx == t.size()) {
                return d;
            }
        } catch (...) {
            return t;
        }
        
    }

public:
    explicit inline ReadArffFile(const String& name_file) : name_file_(name_file) {}

    void LoadFile() {
        file_.open(name_file_);
        if (!file_.is_open()) {
            cerr << "Error to open file: " << name_file_ << endl;
            return;
        }

        String line;
        while (std::getline(file_, line)) {
            if (line.empty() || line[0] == '%') continue;

            String lower = line;
            for (auto &c : lower) c = std::tolower(c);

            if (lower.find("@attribute") == 0) {
                std::istringstream iss(line);
                String atSign, name, type;
                iss >> atSign >> name >> type;
                attributes_.push_back(name);
            } else if (lower.find("@data") == 0) {
                inData_ = true;
                break; // para no começo dos dados
            }
        }
    }

    bool HasNext() {
        return file_.is_open() && file_.peek() != EOF;
    }

    Instance NextInstance() {
        String line;
        while (std::getline(file_, line)) {
            if (line.empty() || line[0] == '%') continue;

            std::istringstream iss(line);
            Vec<Attribute> attributes_list;
            String token;
            while (std::getline(iss, token, ',')) {
                // trim
                auto start = token.find_first_not_of(" \t\r\n");
                auto end   = token.find_last_not_of(" \t\r\n");
                if (start == String::npos) {
                    token.clear();
                } else {
                    token = token.substr(start, end - start + 1);
                }
                attributes_list.push_back(parseToken(token));
            }
            return Instance(attributes_list);
        }
        throw std::out_of_range("No more instances");
    }

    const Vec<String>& GetAttributes() const {
        return attributes_;
    }

    ~ReadArffFile() {
        if (file_.is_open()) file_.close();
    }
};

#endif // READARFFFILE_H
