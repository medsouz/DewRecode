#pragma once
#include <ElDorito/ElDorito.hpp>

// can't be called Utils because we use that for a namespace.. ugh
class PublicUtils : public IUtils
{
public:
	std::string RSAReformatKey(const std::string& key, bool isPrivateKey);
	bool RSACreateSignature(const std::string& privateKey, void* data, size_t dataSize, std::string& signature);
	bool RSAVerifySignature(const std::string& pubKey, const std::string& signature, void* data, size_t dataSize);
	bool RSAGenerateKeyPair(int numBits, std::string& privKey, std::string& pubKey);

	std::string Base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	std::string Base64Decode(const std::string& encoded_string);
	int Base64DecodeBinary(char* b64message, unsigned char* buffer, size_t* length);

	bool Hash32(const std::string& str, uint32_t* out);

	void RemoveCharsFromString(std::string& str, char* charsToRemove);

	void HexStringToBytes(const std::string& in, void* const data, size_t length);
	void BytesToHexString(void* const data, const size_t dataLength, std::string& dest);

	std::string ToLower(const std::string& str);

	void ReplaceCharacters(std::string& str, char replace, char with);
	bool ReplaceString(std::string& str, const std::string& replace, const std::string& with);

	std::wstring WidenString(const std::string& str);
	std::string ThinString(const std::wstring& str);

	std::vector<std::string> SplitString(const std::string& stringToSplit, char delim = ' ');
	std::string Trim(const std::string& string, bool fromEnd = true);
	std::vector<std::string> Wrap(const std::string& string, size_t lineLength);

	HttpRequest HttpSendRequest(const std::wstring& uri, const std::wstring& method, const std::wstring& userAgent, const std::wstring& username, const std::wstring& password, const std::wstring& headers, void* body, DWORD bodySize);
	UPnPResult UPnPForwardPort(bool tcp, int externalport, int internalport, const std::string& ruleName);

	void GetEndpoints(std::vector<std::string>& destVect, const std::string& endpointType);
	
	size_t ExecuteProcess(const std::wstring& fullPathToExe, std::wstring& parameters, size_t secondsToWait);

	PublicUtils();
	~PublicUtils();
private:
	int upnpDiscoverError;
	struct UPNPDev* upnpDevice = nullptr;
};