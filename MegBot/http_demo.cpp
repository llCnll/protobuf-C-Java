#include <iostream>
#include <string>

#include <curl/curl.h>

#include <string.h>

#include "http.pb.h"

using namespace std;

size_t OnWriteData( void* buffer, size_t size, size_t nmemb, void *lpVoid )
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if ( NULL == str || NULL == buffer )
    {
        return -1;
    }

    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}


int main(){

    proto::Point3f resp;

    proto::PointCloud point_cloud;
    point_cloud.set_total(2);
    proto::Point3f* p1 = point_cloud.add_map_points();
    p1->set_x(1);
    p1->set_y(2);
    p1->set_z(3);
    proto::Point3f* p2 = point_cloud.add_map_points();
    p2->set_x(1);
    p2->set_y(2);
    p2->set_z(3);

    string sReq;
    string sResp;

    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if(CURLE_OK != res)
    {
        cout<<"curl init failed"<<endl;
        return 1;
    }

    string url = "http://localhost:8080/http";

    // 序列化请求
    if ( !point_cloud.SerializeToString(&sReq) )
        return 1;

    curl_slist *m_header = NULL;
    m_header = curl_slist_append( m_header, "Content-Type: application/x-protobuf" );  // 设置消息头

    CURL *curl = curl_easy_init();
    curl_easy_setopt( curl, CURLOPT_HTTPHEADER, m_header ); // Header
    curl_easy_setopt( curl, CURLOPT_REFERER, "nginx" );
    curl_easy_setopt( curl, CURLOPT_VERBOSE, 1L );
    curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
    curl_easy_setopt( curl, CURLOPT_NOSIGNAL, 1);

    curl_easy_setopt( curl, CURLOPT_POSTFIELDS, sReq.c_str() );             // Post
    curl_easy_setopt( curl, CURLOPT_POSTFIELDSIZE, sReq.length() );
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, OnWriteData );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, (void*)&sResp );     // Accept data

    CURLcode ret = curl_easy_perform( curl );
    assert( ret == CURLE_OK );
    curl_easy_cleanup( curl );
    curl_slist_free_all( m_header );

    // 反序列化数据
    /*if ( !resp.ParseFromString(sResp) )
        return 1;

    printf( "Response: %s\n", resp.DebugString().c_str() );*/
    cout << sResp << endl;


    return 0;
}
