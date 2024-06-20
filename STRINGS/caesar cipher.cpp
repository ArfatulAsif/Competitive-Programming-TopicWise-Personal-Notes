// Author: (AIA) Registration : 17   

string secret_code = "Here the Algorithm is caesar cipher, uses a secret key techniques like the one in jwt token.";


int helper(string key)
{
    // implement this method as you want it.
}


char encryt(char ch, string code)
{
    int key = helper(code);


    int res_c = ( ch + key) % 128;

    return (char) res_c; 
}

char decrypt(char ch, string code)
{
    int key = helper(code);


    int res_c = ((ch-key) % 128 + 128 ) % 128;

    return (char) res_c;
}




string encrypted_string(string str)
{
    for(int i=0;i<str.size();i++)
    {
        str[i] = encryt(str[i],  secret_code);
    }

    return str;
}


string decrypted_string(string str)
{
    for(int i=0;i<str.size();i++)
    {
        str[i] = decrypt(str[i], secret_code);
    }

    return str;
}



// escape sequence are gonna create a huge problem, which is why to decrypt the encrypted message, make sure that the message is taken as INPUT string. 

