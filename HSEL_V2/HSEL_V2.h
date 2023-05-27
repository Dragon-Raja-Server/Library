#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma pack (1)

namespace HSEL
{
	class CHSEL
	{
	private:
		typedef DWORD KEY_TYPE;//__int64 �̻� ���� ����.
		typedef BYTE GAB_TYPE;//short �̻� ���� ����
		typedef void (CALLBACK CHSEL::*LPHSELFUNC)(char *, const DWORD);
		typedef void (CALLBACK CHSEL::*LPHSELKEYFUNC)();
		typedef WORD INIT_INFO_KEY_TYPE;//short �̻� ���� ����
		typedef WORD INIT_INFO_CRC_TYPE;//short �̻� ���� ����

	public:
		enum eCINFO
		{
			CVERSION				= 2,
			MAX_RD_KEY_ARRAY		= 8,
			MIN_SWAP_BLOCK_COUNT	= 4,
		};

		enum eINIT_FLAG
		{
			ENCRYPT_CMP_BASE					= 0x0000000F,
			ENCRYPT_FAST						= 0x00000001,//�ӵ��� �������� �⵵ȿ�� ����.
			ENCRYPT_SECURE						= 0x00000002,//�ӵ��� �������� ����� �⵵ ȿ�� ����.
		
			SWAP_CMP_BASE						= 0x000000F0,
			SWAP_ON								= 0x00000010,//������ ����
			SWAP_OFF							= 0x00000020,//������ ���� ����
			
			KEY_ROLL_CMP_BASE					= 0x00000F00,
			KEY_ROLL_DYNAMIC					= 0x00000100,//1ȸ�� Encrypt �� Ű�� �ٲ�
			KEY_ROLL_STATIC						= 0x00000200,//ó�� Ű�� ����ؼ� ���

			KEY_INIT_CMP_BASE					= 0x0000F000,//
			KEY_INIT_AUTO						= 0x00001000,//Lib�� Key�� �ڵ����� �������
			KEY_INIT_MANUAL						= 0x00002000,//Key�� �������� ����
		};

		enum eRESULT_CODE
		{
			INIT_SUCCESS						= 0x00000001,
			INIT_MANUAL_FAILED					= 0x00100000,
			INIT_MANUAL_CRC_ERROR				= 0x00200000,

			INIT_ENCRYPT_OPT_FAULT				= 0x00000010,
			INIT_SWAP_OPT_FAULT					= 0x00000100,
			INIT_KEY_ROLL_OPT_FAULT				= 0x00001000,
			INIT_KEY_INIT_FAULT					= 0x00010000,
			INIT_KEY_INIT_FAULT_PLZ_USE_AUTO	= 0x00020000,
			INIT_KEY_INIT_FAULT_PLZ_USE_MANUAL	= 0x00040000,
		};

	private:
		typedef struct tagKeyStore
		{//�ݵ�� Ȧ��
			KEY_TYPE aRDKey[MAX_RD_KEY_ARRAY];
			KEY_TYPE LDESKey;
			KEY_TYPE RDESKey;
		}KEY_STORE, *LPKEY_STORE;

		typedef struct tagGabStore
		{//�ݵ�� Ȧ��
			GAB_TYPE MultiGab;//�������� ������
			GAB_TYPE aRDGab[MAX_RD_KEY_ARRAY];
			GAB_TYPE LDESGab;
			GAB_TYPE RDESGab;
		}GAB_STORE, *LPGAB_STORE;
		
	public:
		typedef struct tagInitInfo
		{//���� ������ Ŭ������ �ٸ��� ����.
			INIT_INFO_KEY_TYPE Key;
			INIT_INFO_CRC_TYPE CRC;

			DWORD dwInitFlag;
			GAB_STORE gs;
			KEY_STORE ks;
		}INIT_INFO, *LPINIT_INFO;

	public:
		CHSEL();
		~CHSEL();

	public:
		eRESULT_CODE InitManual(const INIT_INFO &rInitInfo);//Key�� ���� ���� �ϴ°� �ʿ�
		eRESULT_CODE Init(const DWORD &dwInitFlag);//Flag�� �ʱ�ȭ

		bool GetInitInfo(INIT_INFO &rInitInfo);//���⼭ ���� Info�� ���ڴ��� ����..
		
		bool Encrypt(char *pSrc, const DWORD dwSrcSize);
		bool Decrypt(char *pSrc, const DWORD dwSrcSize);

		bool Encrypt(const char *pSrc, char *pDest, const DWORD dwSrcSize);
		bool Decrypt(const char *pSrc, char *pDest, const DWORD dwSrcSize);

		void GetLastCRC(DWORD &dwCrc);
		void GetLastCRC(WORD &wCrc);
		void GetLastCRC(BYTE &byCrc);

	private:
		bool EncryptInitInfo(INIT_INFO &rInitInfo);
		bool DecryptInitInfo(INIT_INFO &rInitInfo);

		void CALLBACK REN(char *pSrc, const DWORD dwSrcSize);
		void CALLBACK DLEN(char *pSrc, const DWORD dwSrcSize);
		void CALLBACK DREN(char *pSrc, const DWORD dwSrcSize);

		void CALLBACK RDE(char *pSrc, const DWORD dwSrcSize);
		void CALLBACK DLDE(char *pSrc, const DWORD dwSrcSize);
		void CALLBACK DRDE(char *pSrc, const DWORD dwSrcSize);

		void CALLBACK SwapEn(char *pSrc, const DWORD dwSrcSize);
		void CALLBACK SwapDe(char *pSrc, const DWORD dwSrcSize);

		KEY_TYPE CALLBACK GetDataCRC(char *pSrc, const DWORD dwSrcSize);

		void InitKey();
		void InitGab();

		void CALLBACK NextKey();//����Ű ����

		KEY_TYPE MakeKey();
		GAB_TYPE MakeGab();

	private:
		KEY_STORE m_ks;
		GAB_STORE m_gs;

		KEY_TYPE m_CRC;

		DWORD m_dwInitFlag;
		
		LPHSELFUNC m_pFuncEn1;
		LPHSELFUNC m_pFuncEn2;
		LPHSELFUNC m_pFuncEn3;

		LPHSELFUNC m_pFuncDe1;
		LPHSELFUNC m_pFuncDe2;
		LPHSELFUNC m_pFuncDe3;

		LPHSELFUNC m_pFuncEnSwap;
		LPHSELFUNC m_pFuncDeSwap;

		LPHSELKEYFUNC m_pFuncKeyRoll;
	};
}

#pragma pack ()