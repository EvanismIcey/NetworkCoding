
// NetworkCodingFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetworkCodingFile.h"
#include "NetworkCodingFileDlg.h"
#include "afxdialogex.h"
#include "gf.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetworkCodingFileDlg �Ի���



CNetworkCodingFileDlg::CNetworkCodingFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkCodingFileDlg::IDD, pParent)
	, K(0)
	, N(0)
	, Step_info(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_filePath = _T("");
	g_flag = 0;
	g_extName = _T("");
}

void CNetworkCodingFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, K);
	DDX_Text(pDX, IDC_EDIT2, N);
	DDX_Text(pDX, IDC_Progress, Step_info);
	//  DDX_Control(pDX, IDC_Progress, m_Step_info);
}

BEGIN_MESSAGE_MAP(CNetworkCodingFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Open, &CNetworkCodingFileDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_Encode, &CNetworkCodingFileDlg::OnBnClickedEncode)
	ON_BN_CLICKED(IDC_Re_encode, &CNetworkCodingFileDlg::OnBnClickedReencode)
	ON_BN_CLICKED(IDC_Recover, &CNetworkCodingFileDlg::OnBnClickedRecover)
	ON_BN_CLICKED(IDC_Browse, &CNetworkCodingFileDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_Download, &CNetworkCodingFileDlg::OnBnClickedDownload)
END_MESSAGE_MAP()


// CNetworkCodingFileDlg ��Ϣ�������

BOOL CNetworkCodingFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	K = 4;
	N = 6;
	Step_info = "Program Operation Process\r\n**********************\r\n";

	UpdateData(FALSE);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CNetworkCodingFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetworkCodingFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNetworkCodingFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkCodingFileDlg::OnBnClickedOpen()
{
	// TODO: Add your control notification handler code here
	
	//g_flag�������ư�ť���˳��
	if (g_flag != 0 && g_flag!=1){
		Step_info = "Program Operation Process\r\n";
		Step_info += "**********************";
		Scroll();
	}

	Step_info += "Select a file.\r\n";
	Step_info += "1��Start selecting a file.";
	Scroll();
	int flag = 0;
	CFileDialog opendlg(TRUE, _T("*"), _T("*"), OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*;)|*.*||"), NULL);//ѡ���ļ�
	if (opendlg.DoModal() == IDOK)//���ļ���ַ����filePath
	{
		g_filePath = opendlg.GetPathName();
		flag = 1;
	}
	if (flag == 0){
		Step_info += "You don't have a choice of files.\r\n";
		Step_info += "***********************************************************";
		Scroll();
		return;
	}

	USES_CONVERSION;
	char* pfilename = T2A(g_filePath);
	FILE* fp;
	if (fopen_s(&fp, pfilename, "rb")){
		Step_info += "File open failed.";
		Scroll();
		return;
	}
	fclose(fp);
	g_flag = 1;    //g_flagȫ�ֱ����������ư�ť�ĵ�������������ᵼ�³������
	Step_info += "2��File selection success\r\nClick on the Encode button to start encoding.\r\n";
	Step_info += "Please enter the value of N, K, and N>K. if there is no input, will use the default value N=6, K=4.\r\n";
	Step_info += "***********************************************************";
	Scroll();
}


void CNetworkCodingFileDlg::OnBnClickedEncode()
{
	// TODO: Add your control notification handler code here

	//g_flag�������ư�ť���˳��
	if (g_flag !=0){
		DeleteFiles();               //���Ѿ������ɵ�.nc�����ļ�����ɾ��
	}

	UpdateData(TRUE);
	if (g_flag == 0){
		Step_info = "Program Operation Process\r\n**********************\r\nPlease click the Open button to select a file.";
		Scroll();
		return;
	}
	if (N <= 0 || K <= 0){
		Step_info += "Input data is not valid.";
		g_flag = 1;
		Scroll();
		return;
	}
	if (N < K){
		Step_info += "Please input N>=K.";
		g_flag = 1;
		Scroll();
		return;
	}

	Step_info += "Encode.\r\n";
	Step_info += "1��Start encoding.";
	Scroll();


	int i, j;
	USES_CONVERSION;
	char* pfilename = T2A(g_filePath);
	FILE* fp;
	if (fopen_s(&fp, pfilename, "rb")){
		Step_info += "File open failed.";
		Scroll();
		return;
	}
	fseek(fp, 0, SEEK_END);                              //�ļ�ָ���Ƶ��ļ�ĩβ
	long nSize = ftell(fp);                               //��ȡ�ļ����ܳ�
	long nLen = nSize / K + (nSize % K != 0 ? 1 : 0);     //���ļ�ƽ���ֳ�K�ݣ�ÿ�ݳ���ΪnLen���ֽ�
	byte* buffer = new byte[K*nLen];

	for (i = 0; i<K*nLen; i++)//�Ȱ�buffer������0
	{
		buffer[i] = 0;
	}

	fseek(fp, 0, SEEK_SET);     //ָ���ļ���ʼ
	fread(buffer, 1, nSize, fp);//�����ļ���buffer����
	fclose(fp);




	byte** Buf;                                //�ļ����ݴ����ά������K*nLen
	Buf = new byte*[K];                        //��buffer��������ά����Buf
	for (i = 0; i < K; i++){
		Buf[i] = new byte[nLen];
	}
	byte *p = buffer;            //��������buffer����
	for (i = 0; i < K; i++){
		for (j = 0; j < nLen; j++){
			Buf[i][j] = *p;
			p++;
		}
	}
	delete[] buffer;

	Step_info += "2��Get random encoding matrix.\r\nThe encoding matrix is as follows.";
	Scroll();

	/************************************************************************/
	/* Step 2. Get code matrix(N*K)                                         */
	/************************************************************************/
	byte** encodeMatrix;          //�������N*K
	encodeMatrix = new byte*[N];
	for (i = 0; i < N; i++){
		encodeMatrix[i] = new byte[K];
	}

	CString str;
	srand((unsigned)time(NULL));
	for (i = 0; i < N; i++)      //�����������
	{
		for (j = 0; j < K; j++)
		{
			encodeMatrix[i][j] = rand() % 256;
			str.Format(_T("%d"), encodeMatrix[i][j]);
			Step_info += str;
			Step_info += " \t";
		}

		Step_info += "\r\n";
	}

	Step_info += "3��Encoding.";
	Scroll();



	/************************************************************************/
	/* Step 3. Start encoding                                                 */
	/************************************************************************/
	byte** matrix1;                             //�����洢������N*nLen�ľ���
	matrix1 = Multiply(encodeMatrix, Buf, N, K, nLen);

	byte** Mat;                             //�ѱ����������������һ������,����һ��N*(1+K+nLen)�ľ���
	Mat = new byte*[N];
	for (i = 0; i < N; i++){
		Mat[i] = new byte[1 + K + nLen];
	}
	for (i = 0; i < N; i++){                   //��0��ȫΪK
		Mat[i][0] = K;
	}
	for (i = 0; i < N; i++){                   //1��K��Ϊ�������encodeMatrix
		for (j = 1; j <= K; j++){
			Mat[i][j] = encodeMatrix[i][j - 1];
		}
	}
	for (i = 0; i < N; i++){                   //K+1��K+nLenΪ������
		for (j = K + 1; j <= K + nLen; j++){
			Mat[i][j] = matrix1[i][j - K - 1];
		}
	}


	//�Ѿ���matrix2�ֿ�����N��encodeFile�ļ�
	Step_info += "4��The value of K and the encoding vector are written in the corresponding encoded file.Encoding finished.";
	Scroll();

	FILE *fpCd;
	char filename[32];
	g_extName = g_filePath.Right(g_filePath.GetLength() - g_filePath.ReverseFind('.') - 1);//��ȡ�ļ�����չ��,��.nc
	g_extName += ".nc";       //�������ļ����Ϊ.nc�ļ�

	for (i = 1; i <= N; i++)
	{
		_snprintf_s(filename, 32, "encodeFile%d.", i);//�����ļ���Ϊ�ļ�����
		strcat_s(filename, T2A(g_extName.GetBuffer()));//����չ�����ӵ��ļ���
		fopen_s(&fpCd, filename, "wb");
		fwrite(Mat[i - 1], 1, 1 + K + nLen, fpCd);//д��
		g_extName.ReleaseBuffer();
		fclose(fpCd);
	}



	// Clean the memory.



	for (i = 0; i<K; i++)
	{
		delete[]  Buf[i];
	}
	delete Buf;

	for (i = 0; i < N; i++){
		delete[] encodeMatrix[i];
		delete[] matrix1[i];
		delete[] Mat[i];
	}
	delete encodeMatrix;
	delete matrix1;
	delete Mat;

	g_flag = 2;
	Step_info += "Click the Files Browse button to open the current working directory, you can see the encoded files.\r\n";
	Step_info += "Click the Recover button to recover the file or click the Re-encode button to re-encode.\r\n";
	Step_info += "***********************************************************";

	Scroll();
}


void CNetworkCodingFileDlg::OnBnClickedReencode()
{
	// TODO: Add your control notification handler code here
	//g_flag�������ư�ť���˳��
	if (g_flag != 2){   
		if (g_flag == 0){
			Step_info = "Program Operation Process\r\n**********************\r\nPlease click the Open button to select a file.";
			Scroll();
			return;
		}
		if (g_flag == 3)  return; //Ϊ�˿�����������ִֻ��һ��
		Step_info += "Please click the Encode button to start encoding first.";
		g_flag = 3;
		Scroll();
		return;
	}

	Step_info += "Re-encode.\r\n";
	Step_info += "1��Start re-encoding, you can select multiple files to re-encode.";
	Scroll();

	/************************************************************************/
	/* Select files                                                         */
	/************************************************************************/

	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	CString PROGRAM_PATH = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);

	CString str;

	str = "Debug";
	int position = PROGRAM_PATH.Find(str);
	if (position != -1){   //������-1˵�����ڵ���ģʽ����Ҫƴ��·��
		PROGRAM_PATH.Replace(str, _T("NetworkCodingFile"));
	}

	size_t index;
	CString cstrsucstring;
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T("Code Files(*.nc)|*.nc||"));
	TCHAR *pBuffer = new TCHAR[MAX_PATH * 100];//�������ͬʱ��100���ļ�

	filedlg.m_ofn.lpstrInitialDir = PROGRAM_PATH;
	filedlg.m_ofn.lpstrFile = pBuffer;
	filedlg.m_ofn.nMaxFile = MAX_PATH * 100;
	filedlg.m_ofn.lpstrFile[0] = '\0';

	int count = 0;
	CString* cstrfilepath = new CString[100];

	if (filedlg.DoModal() == IDOK)
	{

		POSITION pos = filedlg.GetStartPosition();
		while (pos != NULL)
		{
			cstrfilepath[count] = _T("");
			cstrfilepath[count++] = filedlg.GetNextPathName(pos);//ȡ���ļ�·��
		}
	}
	if (count == 0){
		Step_info += "You don't have a choice of files.\r\n";
		Step_info += "***********************************************************";
		Scroll();
		return;
	}

	char** fileName = new char*[count];
	for (int i = 0; i < count; i++){
		fileName[i] = new char[32];
	}

	int i, j;
	USES_CONVERSION;
	for (i = 0; i < count; i++){//��·���з�����ļ���
		CString fn = cstrfilepath[i].Right(cstrfilepath[i].GetLength() - cstrfilepath[i].ReverseFind('\\') - 1);
		char* ch = T2A(fn);
		for (j = 0; *ch != '\0'; ch++, j++){
			fileName[i][j] = *ch;
		}
		fileName[i][j] = '\0';
	}
	delete[] pBuffer;
	delete[] cstrfilepath;



	/************************************************************************/
	/*  Start re-encoding                                                      */
	/************************************************************************/



	byte** re_encodeMatrix;                     //����������ٱ������
	re_encodeMatrix = new byte*[count];

	for (i = 0; i < count; i++){
		re_encodeMatrix[i] = new byte[count];
	}
	srand((unsigned)time(NULL));
	for (i = 0; i < count; i++)
	{
		for (j = 0; j < count; j++)
		{
			re_encodeMatrix[i][j] = rand() % 256;

		}
	}




	FILE *fp;
	fopen_s(&fp, fileName[0], "rb");
	fseek(fp, 0, SEEK_END);
	long length = 0;
	length = ftell(fp);					  //��ȡencodeFile�ļ��ĳ���
	fclose(fp);


	byte** Buffer;							//�ѱ�����ļ���������
	Buffer = new byte*[count];					//Buffer��������ѡ���ļ��Ķ�����д��
	for (i = 0; i < count; i++){
		Buffer[i] = new byte[length];
	}

	FILE* fpCd;

	for (i = 0; i < count; i++){

		fopen_s(&fpCd, fileName[i], "rb");
		fread(Buffer[i], 1, length, fpCd);
		fclose(fpCd);
	}


	byte** matrix1;                          //ȡ���������ͱ���������
	matrix1 = new byte*[count];
	for (i = 0; i < count; i++){
		matrix1[i] = new byte[length - 1];
	}

	for (i = 0; i < count; i++){
		for (j = 0; j < length - 1; j++){
			matrix1[i][j] = Buffer[i][j + 1];  //Buffer����ĵ�0�д�����ļ�����ǰƽ���ֳɵĸ�������һ�в�����	
		}
	}



	byte** MAT;									//�ٱ���
	MAT = Multiply(re_encodeMatrix, matrix1, count, count, length - 1);





	for (i = 0; i < count; i++){                   //���ٱ������������¶�������
		for (j = 1; j < length; j++){
			Buffer[i][j] = MAT[i][j - 1];
		}
	}


	for (i = 0; i < count; i++)                           //������д���ļ�
	{

		str = fileName[i];
		CString extName = str.Right(str.GetLength() - str.Find('.') + 1);//ȡ���������(1).*.nc
		remove(T2A(str));      //���ٱ������ļ�������
		CString fn;
		fn = _T("re_encodeFile") + extName;
		fopen_s(&fpCd, T2A(fn), "wb");
		fwrite(Buffer[i], 1, length, fpCd);       //д��
		fclose(fpCd);
	}
	Step_info += "2��Re-encoded files have been generated. Re-encoding finished.";
	Scroll();

	for (i = 0; i < count; i++){
		delete[] fileName[i];
		delete[] re_encodeMatrix[i];
		delete[] Buffer[i];
		delete[] matrix1[i];
		delete[] MAT[i];
	}
	delete fileName;
	delete re_encodeMatrix;
	delete Buffer;
	delete matrix1;
	delete MAT;

	g_flag = 2;
	Step_info += "Click the Browse button to open the current working directory, you can see the re_encodeFile files.\r\n";
	Step_info += "Click the Recover button to recover the file.\r\n";
	Step_info += "***********************************************************";
	Scroll();
}


void CNetworkCodingFileDlg::OnBnClickedRecover()
{
	// TODO: Add your control notification handler code here
	//g_flag�������ư�ť���˳��
	if (g_flag!=2){  //��ť���˳��Ŀ���
		if (g_flag == 0){
			Step_info = "Program Operation Process\r\n**********************\r\nPlease click the Open button to select a file.";
			Scroll();
			return;
		}
		if (g_flag == 3) return;//Ϊ�˿�����������ִֻ��һ��
		if (g_flag == 1){
			Step_info += "Please click the Encode button to start encoding first.";
			g_flag = 3;
			Scroll();
			return;
		}
	}


	Step_info += "Recover the file.\r\n";

	Step_info += "1��Select the files to decode,you need select multiple files.";
	Scroll();

	/************************************************************************/
	/* Select files                                                         */
	/************************************************************************/
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	CString PROGRAM_PATH = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);

	CString str;

	str = "Debug";
	int position = PROGRAM_PATH.Find(str);
	if (position != -1){ //������-1˵�����ڵ���ģʽ����Ҫƴ��·��
		PROGRAM_PATH.Replace(str, _T("NetworkCodingFile"));
	}

	size_t index;
	CString cstrsucstring;
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T("Encode Files(*.nc)|*.nc||"));
	TCHAR *pBuffer = new TCHAR[MAX_PATH * 100];//�������ͬʱ��100���ļ�

	filedlg.m_ofn.lpstrInitialDir = PROGRAM_PATH;
	filedlg.m_ofn.lpstrFile = pBuffer;
	filedlg.m_ofn.nMaxFile = MAX_PATH * 100;
	filedlg.m_ofn.lpstrFile[0] = '\0';

	int count = 0;
	CString* cstrfilepath = new CString[100];

	if (filedlg.DoModal() == IDOK)
	{

		POSITION pos = filedlg.GetStartPosition();
		while (pos != NULL)
		{
			cstrfilepath[count] = _T("");
			cstrfilepath[count++] = filedlg.GetNextPathName(pos);//ȡ���ļ�·��
		}
	}
	if (count == 0){
		Step_info += "You don't have a choice of files.\r\n";
		Step_info += "***********************************************************";
		Scroll();
		return;
	}

	char** fileName = new char*[count];    //���������·�����ļ���
	for (int i = 0; i < count; i++){
		fileName[i] = new char[32];
	}
	USES_CONVERSION;
	int i, j;
	for (i = 0; i < count; i++){
		CString fn = cstrfilepath[i].Right(cstrfilepath[i].GetLength() - cstrfilepath[i].ReverseFind('\\') - 1);
		char* ch = T2A(fn);
		for (j = 0; *ch != '\0'; ch++, j++){
			fileName[i][j] = *ch;
		}
		fileName[i][j] = '\0';
	}
	delete[] pBuffer;
	delete[] cstrfilepath;


	/************************************************************************/
	/*  Start decoding.                                                     */
	/************************************************************************/



	int nPart = 0;           //������ű���ǰ�ֳ���ͬ��С���ļ�����
	long nLength = 0;         //��������ļ��ĳ���

	FILE *fp;
	fopen_s(&fp, fileName[0], "rb");
	fread(&nPart, 1, 1, fp);
	fseek(fp, 0, SEEK_END);
	nLength = ftell(fp);
	fclose(fp);
	if (count < nPart){
		Step_info += "Select the number of files is not enough, please click on the Recover button again, select at least ";
		CString str;
		str.Format(_T("%d"), nPart);
		str += " files.";
		Step_info += str;
		Step_info += "\r\n***********************************************************";
		Scroll();
		return;
	}




	byte** MAT;                         //�������nPart�������ļ�����һ��nPart*nLength�ľ���
	MAT = new byte*[nPart];

	for (i = 0; i < nPart; i++){
		MAT[i] = new byte[nLength];
	}


	FILE *fpCd;
	for (i = 0; i < nPart; i++)
	{
		fopen_s(&fpCd, fileName[i], "rb");
		fread(MAT[i], 1, nLength, fpCd);
		fclose(fpCd);
	}



	//�������з���������ͱ�����

	Step_info += "The encoding matrix is as follows.";
	Scroll();
	byte** encodeMAT;                                     //�������ΪnPart*nPart����
	encodeMAT = new byte*[nPart];
	for (i = 0; i < nPart; i++){
		encodeMAT[i] = new byte[nPart];
	}

	for (i = 0; i < nPart; i++){
		for (j = 0; j < nPart; j++){
			encodeMAT[i][j] = MAT[i][j + 1];
			str.Format(_T("%d"), encodeMAT[i][j]);
			str += " \t";
			Step_info += str;
		}
		Step_info += "\r\n";
	}
	Scroll();



	Step_info += "2��Decoding.";
	Scroll();

	byte** MAT1;               //������ΪnPart*(nLength-nPart-1)����
	MAT1 = new byte*[nPart];
	for (i = 0; i < nPart; i++)
	{
		MAT1[i] = new byte[nLength - nPart - 1];
	}
	for (i = 0; i < nPart; i++)
	{
		for (j = 0; j < nLength - nPart - 1; j++)
		{
			MAT1[i][j] = MAT[i][j + 1 + nPart];
		}
	}

	//�Ա����������
	Step_info += "The inverse matrix is as follows.";
	Scroll();

	byte** IvEncodeMAT;
	IvEncodeMAT = Inverse(encodeMAT, nPart);
	if (IvEncodeMAT == NULL){
		Step_info += "The matrix is not full - rank.so the inverse matrix can not be obtained!This file cannot be recovered.You need click on the Recover button again to reselect the files";
		Scroll();
		return;
	}
	for (i = 0; i < nPart; i++){
		for (j = 0; j < nPart; j++){
			str.Format(_T("%d"), IvEncodeMAT[i][j]);
			str += " \t";
			Step_info += str;
		}
		Step_info += "\r\n";
	}
	Scroll();


	//����IvEncodeMAT*MAT1��dataMat�����ս��
	byte** dataMat;
	dataMat = Multiply(IvEncodeMAT, MAT1, nPart, nPart, nLength - nPart - 1);

	Step_info += "3��Original file has been generated. Decoding finished.";
	Scroll();

	//��dataMatд���ļ�
	str = fileName[0];
	CString ext1 = str.Right(str.GetLength() - str.Find('.') - 1);//��jpg.nc
	CString extName = ext1.Left(ext1.GetLength() - ext1.Find('.'));

	CString fn("recovery.");
	fn += extName;


	FILE* fp1;
	fopen_s(&fp1, T2A(fn), "wb");
	for (i = 0; i < nPart; i++)
	{
		fwrite(dataMat[i], 1, nLength - nPart - 1, fp1);//д��
	}
	fclose(fp1);


	//clear the memory
	for (i = 0; i < nPart; i++){
		delete[] fileName[i];
		delete[] MAT[i];
		delete[] encodeMAT[i];
		delete[] MAT1[i];
		delete[] IvEncodeMAT[i];
		delete[] dataMat[i];

	}
	delete fileName;
	delete MAT;
	delete encodeMAT;
	delete MAT1;
	delete IvEncodeMAT;
	delete dataMat;
	g_flag = 2;
	Step_info += "Click the Browse button to open the current working directory, you can see the recovery file.\r\n";
	Step_info += "Click the Clear button, you can clean up the process of the implementation of the program generated files, the recovery file will not be deleted.\r\n";
	Step_info += "***********************************************************";
	Scroll();
}


void CNetworkCodingFileDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	CString PROGRAM_PATH = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);


	CString str("Debug");
	int position = PROGRAM_PATH.Find(str);
	if (position != -1){ //������-1˵�����ڵ���ģʽ����Ҫƴ��·��
		PROGRAM_PATH.Replace(str, _T("NetworkCodingFile"));
	}

	ShellExecute(NULL, NULL, _T("explorer"), PROGRAM_PATH, NULL, SW_SHOW);
}





byte** CNetworkCodingFileDlg::Inverse(byte** G, int n)
{
	//����
	int i;
	int nRow = n;
	int	nCol = n;
	gf_init(8, 0x00000187);
	byte **M = new byte*[nRow];
	for (int j = 0; j<nRow; j++)
	{
		M[j] = new byte[nCol];
	}


	for (int i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			//printf("%d\t", *((GFType*)G + nCol*i + j));
			// M[i][j] = *((GFType*)G + nCol*i + j);
			M[i][j] = *(*(G + i) + j);

		}
		// printf("\n");
	}
	// printf("\n");

	for (int i = 0; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			TRACE("%d\t", M[i][j]);
		}
		TRACE("\n");
	}
	TRACE("\n");

	// Define a variable to record the position of the main element.
	int yPos = 0;

	for (int i = 0; i<nRow; i++)
	{
		// Find the main element which must be non-zero.

		bool bFind = false;

		for (int x = yPos; x<nCol; x++)
		{
			for (int k = i; k<nRow; k++)
			{
				if (M[k][x] != 0)
				{
					// Exchange the two vectors.
					for (int x = 0; x<nCol; x++)
					{
						byte nVal = M[i][x];
						M[i][x] = M[k][x];
						M[k][x] = nVal;
					}										// We have exchanged the two vectors.	
					bFind = true;
					break;
				}
			}
			if (bFind == true)
			{
				yPos = x;
				break;
			}
		}



		for (int j = i + 1; j<nRow; j++)
		{
			// Now, the main element must be nonsingular.
			byte temp = gf_div(M[j][yPos], M[i][yPos]);
			for (int z = 0; z<nCol; z++)
			{
				M[j][z] = gf_add(M[j][z], gf_mul(temp, M[i][z]));
			}
		}
		// 
		yPos++;

	}

	// The matrix becomes a scalar matrix. we need to make more elements become 0 with elementary transformations.
	yPos = 0;
	for (int i = 1; i<nRow; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			if (M[i][j] != 0)
			{
				// the main element is found.
				yPos = j;
				break;
			}
		}
		for (int k = 0; k<i; k++)
		{
			byte temp = gf_div(M[k][yPos], M[i][yPos]);
			for (int z = 0; z<nCol; z++)
			{
				M[k][z] = gf_add(M[k][z], gf_mul(temp, M[i][z]));
			}
		}
	}

	int nRank = 0;
	// Get the rank.
	for (int i = 0; i<nRow; i++)
	{
		int nNonzero = 0;
		for (int j = 0; j<nCol; j++)
		{
			if (M[i][j] != 0)
			{
				nNonzero++;
			}

		}
		// If there is only one nonzero element in the new matrix, it is concluded an original packet is leaked. 
		if (nNonzero > 0)
		{
			// Leaked.
			nRank++;
		}
	}
	for (int i = 0; i<nRow; i++)
	{
		delete[]  M[i];
	}
	delete[] M;


	//����

	int bRet = nRank;

	if (bRet != nRow)
	{

		return NULL;
	}
	/************************************************************************/
	/* Start to get the inverse matrix!                                     */
	/************************************************************************/
	byte **N = new byte*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		N[j] = new byte[2 * nCol];
	}

	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			N[i][j] = G[i][j];
			TRACE("%d\t", N[i][j]);
		}
		for (int j = nCol; j<2 * nCol; j++)
		{
			if (i == j - nCol)
			{
				N[i][j] = 1;
			}
			else
			{
				N[i][j] = 0;
			}
			TRACE("%d\t", N[i][j]);
		}
		TRACE("\n");
	}
	/************************************************************************/
	/* Step 1. Change to a lower triangle matrix.                           */
	/************************************************************************/

	for (i = 0; i<nCol; i++)
	{
		// There must exist a non-zero mainelement.
		TRACE("*********\n");
		if (N[i][i] == 0)
		{
			// Record this line.
			byte temp[200] = { 0 };
			for (int k = 0; k<2 * nCol; k++)
			{
				temp[k] = N[i][k];
			}
			// Exchange
			int nRow = nCol;					// They are the same in essensial.
			for (int z = i + 1; z<nRow; z++)
			{
				if (N[z][i] != 0)
				{
					for (int x = 0; x<2 * nCol; x++)
					{
						N[i][x] = N[z][x];
						N[z][x] = temp[x];
					}
					break;
				}
			}

		}


		for (int j = i + 1; j<nCol; j++)
		{
			// Now, the main element must be nonsingular.
			byte temp = gf_div(N[j][i], N[i][i]);
			for (int z = 0; z<2 * nCol; z++)
			{
				N[j][z] = gf_add(N[j][z], gf_mul(temp, N[i][z]));
			}
		}
	}
	/************************************************************************/
	/* Step 2. Only the elements on the diagonal are non-zero.                  */
	/************************************************************************/
	for (i = 1; i<nCol; i++)
	{
		for (int k = 0; k<i; k++)
		{
			byte temp = gf_div(N[k][i], N[i][i]);
			for (int z = 0; z<2 * nCol; z++)
			{
				N[k][z] = gf_add(N[k][z], gf_mul(temp, N[i][z]));
			}
		}
	}
	/************************************************************************/
	/* Step 3. The elements on the diagonal are 1.                  */
	/************************************************************************/
	for (i = 0; i<nCol; i++)
	{
		if (N[i][i] != 1)
		{
			byte temp = N[i][i];
			for (int z = 0; z<2 * nCol; z++)
			{
				N[i][z] = gf_div(N[i][z], temp);
			}
		}
	}
	/************************************************************************/
	/* Get the new matrix.                                                  */
	/************************************************************************/

	byte **CM = new byte*[nCol];
	for (int j = 0; j<nCol; j++)
	{
		CM[j] = new byte[nCol];
	}
	for (i = 0; i<nCol; i++)
	{
		for (int j = 0; j<nCol; j++)
		{
			CM[i][j] = N[i][j + nCol];
		}

	}

	// Clean the memory.
	gf_uninit();


	for (i = 0; i<nCol; i++)
	{
		delete[]  N[i];
	}
	delete N;

	return CM;
}


byte** CNetworkCodingFileDlg::Multiply(byte** matA, byte** matB, int nRow, int n, int nCol)
{
	int i, j, k;
	int temp;
	gf_init(8, 0x00000187);                //��ʼ����
	byte** Mat;                            //�����洢������˽�� (nRow*nCol)
	Mat = new byte*[nRow];
	for (i = 0; i < nRow; i++){
		Mat[i] = new byte[nCol];
	}
	for (i = 0; i < nRow; i++){            //���������
		for (j = 0; j < nCol; j++){
			temp = 0;
			for (k = 0; k < n; k++){
				temp = gf_add(temp, gf_mul(matA[i][k], matB[k][j]));
			}
			Mat[i][j] = temp;
		}
	}
	gf_uninit();
	return Mat;
}


void CNetworkCodingFileDlg::Scroll()
{
	Step_info += "\r\n";
	GetDlgItem(IDC_Progress)->SetWindowText(Step_info);   //ֻ����ָ���ؼ�������

	CEdit* pedit = (CEdit*)GetDlgItem(IDC_Progress);
	pedit->LineScroll(pedit->GetLineCount());
}


void CNetworkCodingFileDlg::PostNcDestroy()
{
	DeleteFiles();
	CDialog::PostNcDestroy();
}


void CNetworkCodingFileDlg::DeleteFiles()
{
	int i;
	char fileName[32];
	USES_CONVERSION;
	for (i = 1; i <= N; i++)
	{
		_snprintf_s(fileName, 32, "encodeFile%d.", i);
		strcat_s(fileName, T2A(g_extName.GetBuffer()));
		remove(fileName);
	}

	for (i = 1; i <= N; i++)
	{
		_snprintf_s(fileName, 32, "re_encodeFile%d.", i);
		strcat_s(fileName, T2A(g_extName.GetBuffer()));
		remove(fileName);
	}

}


void CNetworkCodingFileDlg::OnBnClickedDownload()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, NULL, _T("https://github.com/WangLei20167/NetworkCoding/tree/master/Chapter2/NetworkCodingFile"), NULL, NULL, SW_SHOWNORMAL);
}
