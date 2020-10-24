#include<string.h>
#include<iostream>
#include<openssl/evp.h>
#include<chrono>
#include<unistd.h>
#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;

const int string_size=20;
const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

struct string_pairs{
    char string1[string_size], string2[string_size];
};
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

//Generate random string
void random_string(char* random_string){
    for (int i = 0; i < string_size; ++i){
        random_string[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
}

void copy_strings(struct string_pairs* pair, char string1[], char string2[]){
    for(int i=0; i<string_size; i++){
        pair->string1[i] = string1[i];
        pair->string2[i] = string2[i];
    }
}


string_pairs find_two_strings(EVP_MD_CTX* ctx, const EVP_MD* md){
    int attempt_count = 0;
    srand(time(0));
    struct string_pairs pairs;
    char rand_string1[string_size], rand_string2[string_size];
    unsigned char digest1[EVP_MAX_MD_SIZE], digest2[EVP_MAX_MD_SIZE];
    unsigned int digest1_length, digest2_length;

    bool match_found = false;
    while(!match_found){
        //Generate random strings
        random_string(rand_string1);
        random_string(rand_string2);

        //Generate digests
        EVP_DigestInit_ex(ctx, md, NULL);
        EVP_DigestUpdate(ctx, rand_string1, strlen(rand_string1));
        EVP_DigestFinal_ex(ctx, digest1, &digest1_length);

        EVP_DigestInit_ex(ctx, md, NULL);
        EVP_DigestUpdate(ctx, rand_string2, strlen(rand_string2));
        EVP_DigestFinal_ex(ctx, digest2, &digest2_length);

        //Check first 24 bits for matches
        bool digest_match = true;
        for(int i=0;i<3;i++){
            if(digest1[i] != digest2[i]){
                digest_match = false;
                break;
            }
        }
        if(digest_match){
            copy_strings(&pairs, rand_string1, rand_string2);
            match_found = true;
        }
        attempt_count++;
    }

    EVP_MD_CTX_destroy(ctx);
    cout<<"Number of attempts: "<<attempt_count<<endl;
    return pairs;
}

string find_matching_digest(EVP_MD_CTX* ctx, const EVP_MD* md, char input[]){
    //srand(time(0));
    int attempt_count = 0;
    char rand_string[string_size];
    unsigned char known_digest[EVP_MAX_MD_SIZE], rand_digest[EVP_MAX_MD_SIZE];
    unsigned int known_digest_length, rand_digest_length;
    //Generate digest for known message
    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, input, strlen(input));
    EVP_DigestFinal_ex(ctx, known_digest, &known_digest_length);

    bool match_found = false;
    while(!match_found){
        random_string(rand_string);
        EVP_DigestInit_ex(ctx,md,NULL);
        EVP_DigestUpdate(ctx,rand_string, strlen(rand_string));
        EVP_DigestFinal_ex(ctx, rand_digest, &rand_digest_length);

        bool digest_match = true;
        for(int i=0;i<3;i++){
            if(known_digest[i] != rand_digest[i]){
                digest_match = false;
                break;
            }
        }
        if(digest_match){ match_found = true;}
        attempt_count++;
    }
    EVP_MD_CTX_destroy(ctx);
    cout<<"Number of attempts: "<<attempt_count<<endl;
    string return_string = convertToString(rand_string, sizeof(rand_string)/sizeof(char));
    return return_string;
}

int main(int argc, char* argv[]){
    EVP_MD_CTX* ctx;
    const EVP_MD* md;
    char md_type[] = "md5";

    OpenSSL_add_all_algorithms();
    md = EVP_get_digestbyname(md_type);
    ctx = EVP_MD_CTX_create();

    //Find two strings with matching digest
    // struct string_pairs matching_strings = find_two_strings(ctx, md);
    //cout<<"Matching strings: "<<matching_strings.string1<<", "<<matching_strings.string2<<endl;

    //Find string with a digest matching a known message
    string matching_string;
    char to_match[] = "This is a string to be matched";
    matching_string =find_matching_digest(ctx, md, to_match);
    cout<<"Matching string: "<<matching_string<<endl;

    return 0;
}
