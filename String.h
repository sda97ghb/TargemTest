#pragma once

#include "SharedData.h"

namespace utils {
    struct StringData;

    class String {
    public:
        String();
        String(const char* cString);
        String(const String& other);
        ~String();

        String& operator =(const char* cString);
        String& operator =(const String& other);

        const char* rawString() const;

        friend String operator +(const String& l, const String& r);

        friend bool operator <(const String& l, const String& r);
        friend bool operator <=(const String& l, const String& r);
        friend bool operator >(const String& l, const String& r);
        friend bool operator >=(const String& l, const String& r);
        friend bool operator ==(const String& l, const String& r);
        friend bool operator !=(const String& l, const String& r);

        static int compare(const String& l, const String& r);

    private:
        String(SharedData<StringData>* sharedData);

        SharedData<StringData>* m_sharedData;
    };

    String operator +(const String& l, const String& r);

    bool operator <(const String& l, const String& r);
    bool operator <=(const String& l, const String& r);
    bool operator >(const String& l, const String& r);
    bool operator >=(const String& l, const String& r);
    bool operator ==(const String& l, const String& r);
    bool operator !=(const String& l, const String& r);

    template <typename Stream_t>
    Stream_t& operator <<(Stream_t& stream, const String& str) {
        return stream << str.rawString();
    }
}
