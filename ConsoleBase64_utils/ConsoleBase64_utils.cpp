// ConsoleBase64_utils.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <boost/beast/core/detail/base64.hpp>
//#include <boost/interprocess/file_mapping.hpp>
//#include <boost/interprocess/mapped_region.hpp>

using namespace std;

string base64_encode(std::uint8_t const* data, std::size_t len)
{
    std::string dest;
    dest.resize(boost::beast::detail::base64::encoded_size(len));
    dest.resize(boost::beast::detail::base64::encode(&dest[0], data, len));
    return dest;
}




int main()
{
    std::ifstream is("d:/Develop/Cpp/tmp/test_x.ods", std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char* buffer = new char[length];

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read(buffer, length);

        if (is)
            std::cout << "all characters read successfully.";
        else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();

        // ...buffer contains the entire file...
        //cout << "\n buff \n"<< buffer;
        cout << '\n' << base64_encode(reinterpret_cast<uint8_t*>(buffer), length);
        delete[] buffer;
    }

    /*const boost::interprocess::mode_t mode = boost::interprocess::read_only;
    boost::interprocess::file_mapping fm("d:/Develop/Cpp/tmp/test.txt ", mode);
    boost::interprocess::mapped_region region(fm, mode, 0, 0);
    const char* begin = static_cast<const char*>(region.get_address());
    const char* pos = std::find(begin, begin + region.get_size(), '\1');*/
    
    /*uint8_t dataArray[] = {1,2,3,4};
    cout << base64_encode(dataArray, 4);*/
}
