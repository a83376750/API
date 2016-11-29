#pragma once
#include <string>
#include <cstdint>

using namespace std;
class MD5
{
public:
	~MD5() = default;
	struct md5_context
	{
		uint32_t total[2];
		uint32_t state[4];
		uint8_t buffer[64];
	};

	void md5_starts(struct md5_context *ctx);
	void md5_process(struct md5_context *ctx, uint8_t data[64]);
	void md5_update(struct md5_context *ctx, uint8_t *input, uint32_t length);
	void md5_finish(struct md5_context *ctx, uint8_t digest[16]);

public:
	//! construct a CMD5 from any buffer  
	void GenerateMD5(unsigned char* buffer, int bufferlen);

	//! construct a CMD5  
	MD5();

	//! construct a md5src from char *  
	MD5(const char * md5src);

	//! construct a CMD5 from a 16 bytes md5  
	MD5(unsigned long* md5src);

	//! add a other md5  
	MD5 operator +(MD5 adder);

	//! just if equal  
	bool operator ==(MD5 cmper);

	//! give the value from equer  
	// void operator =(CMD5 equer);  

	//! to a string  
	string ToString();

	unsigned long m_data[4];
};

