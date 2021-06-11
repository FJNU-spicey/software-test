#include<windows.h>

#include<iostream>

#include<shlwapi.h>

#include<iomanip>

#pragma comment(lib,"shlwapi.lib")

inline bool TestSet(DWORD dwTarget, DWORD dwMask)
{
 return((dwTarget & dwMask)==dwMask);
}
#define SHOWMASK(dwTarget,type)\
 if(TestSet(dwTarget,PAGE_##type))\
{std::cout<<","<<#type;}

void ShowProtection(DWORD dwTarget)
{
 SHOWMASK(dwTarget,READONLY);

 SHOWMASK(dwTarget,GUARD);

 SHOWMASK(dwTarget,NOCACHE);

 SHOWMASK(dwTarget,READWRITE);

 SHOWMASK(dwTarget,WRITECOPY);

 SHOWMASK(dwTarget,EXECUTE);

 SHOWMASK(dwTarget,EXECUTE_READ);

 SHOWMASK(dwTarget,EXECUTE_READWRITE);

 SHOWMASK(dwTarget,EXECUTE_WRITECOPY);

 SHOWMASK(dwTarget,NOACCESS);
}

void WalkVM(HANDLE hProcess)
{
 // ���ȣ����ϵͳ��Ϣ
 SYSTEM_INFO si;

 ::ZeroMemory(&si,sizeof(si));

 ::GetSystemInfo(&si);
 // ����Ҫ�����Ϣ�Ļ�����
 MEMORY_BASIC_INFORMATION mbi;

 ::ZeroMemory(&mbi,sizeof(mbi));

 // ѭ������Ӧ�ó����ַ�ռ�
 LPCVOID pBlock=(LPVOID)si.lpMinimumApplicationAddress;

 while(pBlock<si.lpMaximumApplicationAddress)
 {
   // �����һ�������ڴ�����Ϣ
   if(::VirtualQueryEx(
     hProcess,          // ��صĽ���

     pBlock,            // ��ʼλ��

     &mbi,            // ������
     sizeof(mbi))==sizeof(mbi))  // ��С��ȷ��
   {
     
     LPCVOID pEnd=(PBYTE)pBlock+mbi.RegionSize;

     TCHAR szSize[MAX_PATH];

     ::StrFormatByteSize(mbi.RegionSize,szSize,MAX_PATH);
     
     std::cout.fill('0');

     std::cout<<std::hex<<std::setw(8)<<(DWORD)pBlock<<"    "<<std::hex<<std::setw(8)<<(DWORD)pEnd<<"	("<<szSize<<")";
     
	 // ��ʾ�ڴ���״̬

     switch(mbi.State)
     {
       case MEM_COMMIT:
         std::cout<<"   Committed\n\n";
         break;

       case MEM_FREE:
         std::cout<<"   Free\n\n";
         break;

       case MEM_RESERVE:
         std::cout<<"   Reserved\n\n";
         break;
     }
    
     std::cout<<std::endl;
     // �ƶ���ָ�뵽��һ���ڴ��
     pBlock=pEnd;
   }
 }
}
void main()
{
 // ������ǰ���̵������ڴ�
	std::cout<<"\n  * * * VirtualQueryEx�������������ڴ� * * *\n\n��ʼ��ַ    ��ֹ��ַ	  ����	    �ڴ���״̬\n\n";

	::WalkVM(::GetCurrentProcess());
}