#include "Utils.hpp"
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <functional>
#include <cctype>
#include <codecvt>
#include <iomanip>

#include "ElDorito.hpp"

static const std::string base64_chars =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string PublicUtils::RSAReformatKey(bool isPrivateKey, std::string key)
{
	size_t pos = 0;
	std::string returnKey;
	while (pos < key.length())
	{
		int toCopy = key.length() - pos;
		if (toCopy > 64)
			toCopy = 64;
		returnKey += key.substr(pos, toCopy);
		returnKey += "\n";
		pos += toCopy;
	}
	std::string keyType = (isPrivateKey ? "RSA PRIVATE KEY" : "PUBLIC KEY"); // public keys don't have RSA in the name some reason

	std::stringstream ss;
	ss << "-----BEGIN " << keyType << "-----\n" << returnKey << "-----END " << keyType << "-----\n";
	return ss.str();
}

bool PublicUtils::RSACreateSignature(std::string privateKey, void* data, size_t dataSize, std::string& signature)
{
	// TODO3:
	return false;
}

bool PublicUtils::RSAVerifySignature(std::string pubKey, std::string signature, void* data, size_t dataSize)
{
	// TODO3:
	return false;
}

bool PublicUtils::RSAGenerateKeyPair(int numBits, std::string& privKey, std::string& pubKey)
{
	// TODO3:
	return false;
}

std::string PublicUtils::Base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}

std::string PublicUtils::Base64Decode(std::string const& encoded_string)
{
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4)
		{
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

int PublicUtils::Base64DecodeBinary(char* b64message, unsigned char* buffer, size_t* length)
{
	// TODO3:
	return 0;
}

// Calculates the length of a decoded string
size_t calcDecodeLength(const char* b64input)
{
	size_t len = strlen(b64input),
		padding = 0;

	if (b64input[len - 1] == '=' && b64input[len - 2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len - 1] == '=') //last char is =
		padding = 1;

	return (len * 3) / 4 - padding;
}

// Decodes a base64 encoded string, buffer should be allocated before calling
// If buffer is null it'll just give the decoded data length
/*int PublicUtils::Base64DecodeBinary(char* b64message, unsigned char* buffer, size_t* length)
{
	int decodeLen = calcDecodeLength(b64message);
	if (!buffer)
	{
		*length = decodeLen;
		return 1;
	}

	BIO* bio = BIO_new_mem_buf(b64message, -1);
	BIO* b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // do not use newlines to flush buffer
	*length = BIO_read(bio, buffer, strlen(b64message));
	if (*length != decodeLen) // length should equal decodeLen, else something went horribly wrong
		return 2;

	BIO_free_all(bio);

	return 0;
}*/

void PublicUtils::RemoveCharsFromString(std::string &str, char* charsToRemove)
{
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i)
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
}

void PublicUtils::HexStringToBytes(const std::string &in, void *const data, size_t length)
{
	unsigned char   *byteData = reinterpret_cast<unsigned char*>(data);

	std::stringstream hexStringStream; hexStringStream >> std::hex;
	for (size_t strIndex = 0, dataIndex = 0; strIndex < (length * 2); ++dataIndex)
	{
		// Read out and convert the string two characters at a time
		const char tmpStr[3] = { in[strIndex++], in[strIndex++], 0 };

		// Reset and fill the string stream
		hexStringStream.clear();
		hexStringStream.str(tmpStr);

		// Do the conversion
		int tmpValue = 0;
		hexStringStream >> tmpValue;
		byteData[dataIndex] = static_cast<unsigned char>(tmpValue);
	}
}

void PublicUtils::BytesToHexString(void *const data, const size_t dataLength, std::string &dest)
{
	unsigned char       *byteData = reinterpret_cast<unsigned char*>(data);
	std::stringstream   hexStringStream;

	hexStringStream << std::hex << std::setfill('0');
	for (size_t index = 0; index < dataLength; ++index)
		hexStringStream << std::setw(2) << static_cast<int>(byteData[index]);
	dest = hexStringStream.str();
}

void PublicUtils::ReplaceCharacters(std::string& str, char find, char replaceWith)
{
	for( unsigned i = 0; i < str.length(); ++i )
		if( str[i] == find )
			str[i] = replaceWith;
}

bool PublicUtils::ReplaceString(std::string &str, const std::string &replace, const std::string &with)
{
	size_t start_pos = str.find(replace);
	bool found = false;
	while (start_pos != std::string::npos)
	{
		str.replace(start_pos, replace.length(), with);
		start_pos += with.length();
		found = true;
		start_pos = str.find(replace, start_pos);
	}
	return found;
}

std::wstring PublicUtils::WidenString(const std::string &s)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
	return utf16conv.from_bytes(s);
}

std::string PublicUtils::ThinString(const std::wstring &str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8conv;
	return utf8conv.to_bytes(str);
}

std::string PublicUtils::ToLower(const std::string &str)
{
	std::string retValue(str);
	std::transform(retValue.begin(), retValue.end(), retValue.begin(), ::tolower);
	return retValue;
}

std::vector<std::string> PublicUtils::SplitString(const std::string &stringToSplit, char delim)
{
	std::vector<std::string> retValue;
	std::stringstream ss(stringToSplit);
	std::string item;
	while( std::getline(ss, item, delim) )
	{
		retValue.push_back(item);
	}
	return retValue;
}

// trim from start
static inline std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s)
{
	return ltrim(rtrim(s));
}

std::string PublicUtils::Trim(const std::string &string, bool fromEnd)
{
	std::string retValue(string);
	if( fromEnd ) // From End
	{
		retValue.erase(std::find_if(retValue.rbegin(), retValue.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), retValue.end());
	}
	else // From Start
	{
		retValue.erase(retValue.begin(), std::find_if(retValue.begin(), retValue.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	return retValue;
}

std::vector<std::string> PublicUtils::Wrap(const std::string &string, size_t lineLength)
{
	std::stringstream sstream;
	sstream << string;

	std::vector<std::string> lines;
	while( sstream.good() ) // Copy all lines into string
	{
		std::string currentLine;
		std::getline(sstream, currentLine);
		lines.push_back(currentLine);
	}

	std::vector<std::string> retValue;

	for( unsigned i = 0; i < lines.size(); ++i )
	{
		std::string currentLine(lines[i]);
		while( currentLine.length() > lineLength )
		{
			int wordEnd = lineLength;
			while( wordEnd > 0 && !std::isspace(currentLine[wordEnd]) )
				--wordEnd;
			if( wordEnd <= 0 )
				wordEnd = lineLength;

			retValue.push_back(currentLine.substr(0, wordEnd));
			currentLine = currentLine.substr(wordEnd, std::string::npos);
		}

		retValue.push_back(currentLine);
	}

	return retValue;
}