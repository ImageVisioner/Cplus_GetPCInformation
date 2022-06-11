#include <WinSock2.h>
#include <Iphlpapi.h>
#include <iostream>
using namespace std;
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库

int main(int argc, char* argv[])
{
    //PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    //得到结构体大小,用于GetAdaptersInfo参数
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
    int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    //记录网卡数量
    int netCardNum = 0;
    //记录每张网卡上的IP地址数量
    int IPnumPerNetCard = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        //如果函数返回的是ERROR_BUFFER_OVERFLOW
        //则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
        //这也是说明为什么stSize既是一个输入量也是一个输出量
        //释放原来的内存空间
        delete pIpAdapterInfo;
        //重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
        nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
    }
    if (ERROR_SUCCESS == nRel)
    {
        //输出网卡信息
         //可能有多网卡,因此通过循环去判断
        while (pIpAdapterInfo)
        {
            cout << "网卡数量：" << ++netCardNum << endl;
            cout << "网卡名称：" << pIpAdapterInfo->AdapterName << endl;
            cout << "网卡描述：" << pIpAdapterInfo->Description << endl;
            switch (pIpAdapterInfo->Type)
            {
            case MIB_IF_TYPE_OTHER:
                cout << "网卡类型：" << "OTHER" << endl;
                break;
            case MIB_IF_TYPE_ETHERNET:
                cout << "网卡类型：" << "ETHERNET" << endl;
                break;
            case MIB_IF_TYPE_TOKENRING:
                cout << "网卡类型：" << "TOKENRING" << endl;
                break;
            case MIB_IF_TYPE_FDDI:
                cout << "网卡类型：" << "FDDI" << endl;
                break;
            case MIB_IF_TYPE_PPP:
                printf("PP\n");
                cout << "网卡类型：" << "PPP" << endl;
                break;
            case MIB_IF_TYPE_LOOPBACK:
                cout << "网卡类型：" << "LOOPBACK" << endl;
                break;
            case MIB_IF_TYPE_SLIP:
                cout << "网卡类型：" << "SLIP" << endl;
                break;
            default:

                break;
            }
            cout << "网卡MAC地址：";
            for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
                if (i < pIpAdapterInfo->AddressLength - 1)
                {
                    printf("%02X-", pIpAdapterInfo->Address[i]);
                }
                else
                {
                    printf("%02X\n", pIpAdapterInfo->Address[i]);
                }
            cout << "网卡IP地址如下：" << endl;
            //可能网卡有多IP,因此通过循环去判断
            IP_ADDR_STRING* pIpAddrString = &(pIpAdapterInfo->IpAddressList);
            do
            {
                cout << "该网卡上的IP数量：" << ++IPnumPerNetCard << endl;
                cout << "IP 地址：" << pIpAddrString->IpAddress.String << endl;
                cout << "子网地址：" << pIpAddrString->IpMask.String << endl;
                cout << "网关地址：" << pIpAdapterInfo->GatewayList.IpAddress.String << endl;
                pIpAddrString = pIpAddrString->Next;
            } while (pIpAddrString);
            pIpAdapterInfo = pIpAdapterInfo->Next;
            cout << "--------------------------------------------------------------------" << endl;
        }

    }
    //释放内存空间
    if (pIpAdapterInfo)
    {
        delete pIpAdapterInfo;
    }

    return 0;
}