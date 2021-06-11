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
 // 首先，获得系统信息
 SYSTEM_INFO si;

 ::ZeroMemory(&si,sizeof(si));

 ::GetSystemInfo(&si);
 // 分配要存放信息的缓冲区
 MEMORY_BASIC_INFORMATION mbi;

 ::ZeroMemory(&mbi,sizeof(mbi));

 // 循环整个应用程序地址空间
 LPCVOID pBlock=(LPVOID)si.lpMinimumApplicationAddress;

 while(pBlock<si.lpMaximumApplicationAddress)
 {
   // 获得下一个虚拟内存块的信息
   if(::VirtualQueryEx(
     hProcess,          // 相关的进程

     pBlock,            // 开始位置

     &mbi,            // 缓冲区
     sizeof(mbi))==sizeof(mbi))  // 大小的确认
   {
     
     LPCVOID pEnd=(PBYTE)pBlock+mbi.RegionSize;

     TCHAR szSize[MAX_PATH];

     ::StrFormatByteSize(mbi.RegionSize,szSize,MAX_PATH);
     
     std::cout.fill('0');

     std::cout<<std::hex<<std::setw(8)<<(DWORD)pBlock<<"    "<<std::hex<<std::setw(8)<<(DWORD)pEnd<<"	("<<szSize<<")";
     
	 // 显示内存区状态

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
     // 移动块指针到下一个内存块
     pBlock=pEnd;
   }
 }
}
void main()
{
 // 遍历当前进程的虚拟内存
	std::cout<<"\n  * * * VirtualQueryEx函数遍历虚拟内存 * * *\n\n起始地址    终止地址	  长度	    内存区状态\n\n";

	::WalkVM(::GetCurrentProcess());
}