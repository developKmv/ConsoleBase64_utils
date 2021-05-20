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





int main(int argc, char* argv[])
{
    std::ifstream is(argv[1], std::ifstream::binary);
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

        ofstream outf("output_to_base64.txt");
        outf << base64_encode(reinterpret_cast<uint8_t*>(buffer), length);

        std::cout << "\nall characters write successfully.";

        delete[] buffer;
    }

}
