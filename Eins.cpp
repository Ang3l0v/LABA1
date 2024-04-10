#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
class encoder
{
private:
	char* _key;
	unsigned int _length;
public:
	encoder(unsigned char const* key, unsigned int length);
	~encoder() { delete _key; }
	encoder(encoder const& ob);
	void encode(char const* infile, char const* outfile, bool flag);
	void mutator(char const* key);
};
void encoder::mutator(char const* key) 
{
    delete this->_key;
    this->_length = strlen((char*)key);
    this->_key = new char[this->_length + 1];
    int i;
    for (i = 0; i < _length; i++) 
    {
        this->_key[i] = key[i];
    }
    this->_key[i] = '\0';
}
encoder::encoder(unsigned char const* key, unsigned int length)
{
	this->_key = new char[length + 1];
	this->_length = length;
	int i;
	for (i = 0; i < length; i++)
	{
		this->_key[i] = key[i];
	}
	this->_key[i] = '\0';
}
encoder::encoder(encoder const& ob)
{
	_length = ob._length;
	_key = new char[_length + 1];
	int i;
	for (i = 0; i < _length; i++)
	{
		_key[i] = ob._key[i];
	}
	_key[i] = '\0';
}
void encoder::encode(char const* infile, char const* outfile, bool flag)
{
    unsigned char string[256];
    int i = 0, j = 0;
    for (i = 0; i < 256; i++)
    {
        string[i] = i;
    };
    for (i = 0; i < 256; i++)
    {
        j = (j + string[i] + _key[i % _length]) % 256;
        swap(string[i], string[j]);
    }
    ifstream inFile(infile);
    ofstream outFile(outfile);
    char x;
    j = 0;
    i = 0;
    char temp = 0;
    while (inFile.read(&x, 1))
    {
        i = (i + 1) % 256;
        j = (j + string[i]) % 256;
        swap(string[i], string[j]);
        temp = string[(string[i] + string[j]) % 256] ^ x;
        outFile << temp;
    }
    inFile.close();
    outFile.close();
}
int main()
{
    encoder ob((unsigned char const*)"abc", 3);
    encoder ob2(ob);
    ob.mutator("def");
    ob2.encode("1.txt", "2.txt", 1);
}