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

public:
    ReadArffFile(const String& name_file) : name_file_(name_file) {}

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
        return file_.good();
    }

    Instance NextInstance() {
        String line;
        while (std::getline(file_, line)) {
            if (line.empty() || line[0] == '%') continue;

            Instance inst;
            // std::istringstream iss(line);
            // String token;
            // while (std::getline(iss, token, ',')) {
            //     // trim
            //     token.erase(0, token.find_first_not_of(" \t\r\n"));
            //     token.erase(token.find_last_not_of(" \t\r\n") + 1);
            //     inst.values.push_back(token);
            // }
            // return inst;
            return new Instance;
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
