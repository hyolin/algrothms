#include <iostream>
#include <codecvt>
#include <string>
#include <locale>

template <typename T>
std::string to_utf8(const std::basic_string<T, 
                    std::char_traits<T>, 
                    std::allocator<T>>& source)
{
    std::string res;
    std::wstring_convert<std::codecvt_utf8_utf16<T>, T> convert;
    res = convert.to_bytes(source);
    return res;
}

template <typename T>
void from_utf8(const std::string& source, std::basic_string<T,
                                    std::char_traits<T>, 
                                    std::allocator<T>>& res)
{
    std::wstring_convert<std::codecvt_utf8_utf16<T>, T> convert;
    res = convert.from_bytes(source);
}


int main()
{
    std::u16string s16;
    std::string s = u8"你好！";
    from_utf8(s, s16);
    std::cout<<to_utf8(s16);
    return 0;
}
