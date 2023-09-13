// @jung june


#include "Network/SCPacketEncrytion.h"

FSCPacketEncrytion::FSCPacketEncrytion()
{
}

FSCPacketEncrytion::~FSCPacketEncrytion()
{
}
void FSCPacketEncrytion::Initialize()
{
}

void FSCPacketEncrytion::CreateKey_RSA(std::string& Modulus, std::string& Exponent)
{
	BIGNUM* BN = BN_new();
	if (BN_set_word(BN, RSA_F4) != 1)
	{
		// Invalid BIGNUM
		return;
	}

	RSA_Key = RSA_new();
	RSA_generate_key_ex(RSA_Key, 2048, BN, nullptr);

	if (RSA_check_key(RSA_Key) == -1)
	{
		// Invalid RSA_Key
		return;
	}

	TArray<uint8> ModulusData;
	ModulusData.SetNumUninitialized(BN_num_bytes(RSA_get0_n(RSA_Key)));

	TArray<uint8> ExponentData;
	ExponentData.SetNumUninitialized(BN_num_bytes(RSA_get0_e(RSA_Key)));

	BN_bn2bin(RSA_get0_n(RSA_Key), ModulusData.GetData()); BN_bn2bin(RSA_get0_e(RSA_Key), ExponentData.GetData());

	// Bytes to string
	Modulus.append(reinterpret_cast<const char*>(ModulusData.GetData()), ModulusData.Num());
	Exponent.append(reinterpret_cast<const char*>(ExponentData.GetData()), ExponentData.Num());

	BN_free(BN);
}

void FSCPacketEncrytion::SetRC4Key(uint8* Data, int32 Size)
{
	const int32 ResultLength = RSA_private_decrypt(Size, Data, Data, RSA_Key, RSA_PKCS1_OAEP_PADDING);

	RC4_set_key(&RC4_Key, ResultLength, Data);
	bSetRC4Key = true;
}

void FSCPacketEncrytion::RC4Process(TArray<uint8>& InOutData)
{
	if (IsValid() == false)
	{
		return;
	}

	RC4(&RC4_Key, InOutData.Num(), InOutData.GetData(), InOutData.GetData());
}


void FSCPacketEncrytion::Clear()
{
	if (RSA_Key != nullptr && RSA_check_key(RSA_Key) == 1)
	{
		RSA_free(RSA_Key);
	}
	bSetRC4Key = false;
}

bool FSCPacketEncrytion::IsValid()
{
	return bSetRC4Key;
}

void FSCPacketEncrytion::CeatePublicKey_RSA(const std::string& Modulus, const std::string& Exponent)
{
	RSA_PublicKey = RSA_new();
	BIGNUM* N = BN_new();
	BIGNUM* E = BN_new();
	BN_bin2bn(reinterpret_cast<const uint8*>(Modulus.c_str()), Modulus.length(), N); BN_bin2bn(reinterpret_cast<const uint8*>(Exponent.c_str()), Exponent.length(), E);
	RSA_set0_key(RSA_PublicKey, N, E, nullptr);
	BN_free(N);
	BN_free(E);
}

void FSCPacketEncrytion::CreateRC4()
{
	uint8 Key[256];
	RAND_bytes(Key, sizeof(Key));
	RC4_set_key(&RC4_ServerKey, 256, Key);
	RSA_public_encrypt(256, Key, Key, RSA_Key, RSA_PKCS1_OAEP_PADDING);
	SetRC4Key(Key, 256);
}


