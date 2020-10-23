#include <string>
#include<iostream>
#include<openssl/evp.h>
#include<chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

struct string_pairs{
    char string1[], string2[];
};

//Generate random string
void random_len24_string(char random_string[24]){

    for (int i = 0; i < 24; ++i)
        random_string[i] += alphanum[rand() % (sizeof(alphanum) - 1)];


}
string_pairs find_two_strings(EVP_MD_CTX* ctx, const EVP_MD* md){
    struct string_pairs pairs;
    char rand_string1[24], rand_string2[24];

    bool match_found = false;
    while(!match_found){
        random_len24_string(&rand_string1);
        random_len24_string(&rand_string2);

        cout<<rand_string1<<", "<<rand_string2<<endl;


    }


    cout<<rand_string1<< " , "<<rand_string2<<endl;

}

char* find_matching_digest(EVP_MD_CTX* ctx, const EVP_MD* md, char input[]){





}





int main(int argc, char* argv[]){
    EVP_MD_CTX* ctx;
    char md_type[] = "md5";
    OpenSSL_add_all_algorithms();
    const EVP_MD* md = EVP_get_digestbyname(md_type);
    //EVP_DigestInit(ctx, md);


    auto start = high_resolution_clock::now();
    struct string_pairs matching_strings = find_two_strings(ctx, md);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"Matching strings: "<<matching_strings.string1<<", "<<matching_strings.string2<<endl;
    cout<<"Hash runtime: "<<duration.count()<< " microseconds"<<endl<<endl;

    char to_match[] = "this is a string";
    char* matching_string;
    start = high_resolution_clock::now();
    matching_string =find_matching_digest(ctx, md, to_match);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Matching string: "<<matching_string<<endl;
    cout<<"Hash runtime: "<<duration.count()<< " microseconds"<<endl;

    return 0;
}
