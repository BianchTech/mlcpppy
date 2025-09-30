#include "mlcpppy/data_streams/read_arff_file.h"

int main()
{
    auto reader = new ReadArffFile("../data/sea_dataset.arff");
    reader->LoadFile();

    while (reader->HasNext())
    {
        Instance inst  = reader->NextInstance();
        cout << inst << endl;
    }
    
    return 0;
}
