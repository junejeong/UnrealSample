// @jung june

#pragma once

#include "SC.h"


#define UI UI_ST

THIRD_PARTY_INCLUDES_START
#include <openssl/rsa.h>
#include <openssl/rc4.h>
#include <openssl/rand.h>
THIRD_PARTY_INCLUDES_END

#undef UI
/**
 * 
 */
class FSCPacketEncrytion
{
public:
public:
	FSPPacketEncrytion();
	virtual ~FSPPacketEncrytion();

	void Initialize();
	void CreateKey_RSA(std::string& Modulus, std::string& Exponent);
	void SetRC4Key(uint8* Data, int32 Size);
	void RC4Process(TArray<uint8>& InOutData);
	void Clear();

	bool IsValid();

	void CeatePublicKey_RSA(const std::string& Modulus, const std::string& Exponent);
	void CreateRC4();

private:
	RSA* RSA_Key;
	RSA* RSA_PublicKey;
	bool bSetRC4Key = false;

	RC4_KEY RC4_Key;
	RC4_KEY RC4_ServerKey;
};
