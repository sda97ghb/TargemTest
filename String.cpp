#include <iostream>
#include <cstring>

#include "String.h"
#include "Log.h"

namespace utils {
    namespace raw_string {
        size_t getSize(const char* rawString) {
            return strlen(rawString) + 1; // length + 1 из-за null символа на конце
        }

        int compareCaseInsensitive(const char* s1, const char* s2) {
            if (s1 == s2)
                return 0;
            int result;
            while ((result = tolower(*s1) - tolower(*s2++)) == 0)
                if (*s1++ == '\0')
                    break;
            return result;
        }
    }

    struct StringData {
        static const char* EMPTY_STRING;

        char* m_rawString;
        size_t m_rawStringSize;

        StringData() :
            m_rawString(nullptr),
            m_rawStringSize(0) {
            Log::d("Create StringData");
            setRawString(EMPTY_STRING);
        }

        StringData(const char* rawString) :
            m_rawString(nullptr),
            m_rawStringSize(0) {
            Log::d("Create StringData");
            setRawString(rawString);
        }

        ~StringData() {
            Log::d("Delete StringData");
            deallocate();
        }

        void setRawString(const char* rawString) {
            allocate(raw_string::getSize(rawString));
            memcpy(m_rawString, rawString, m_rawStringSize);
        }

        void append(const char* rawString) {
            size_t oldSize = m_rawStringSize - 1; // нет нужды копировать null на конце
            const char* oldString = m_rawString;

            size_t appendSize = raw_string::getSize(rawString);

            size_t newSize = oldSize + appendSize;
            char* newString = new char[newSize];
            memcpy(newString, oldString, oldSize);
            memcpy(newString + oldSize, rawString, appendSize);

            deallocate();
            m_rawString = newString;
            m_rawStringSize = newSize;
        }

    protected:
        void allocate(size_t size) {
            deallocate();
            m_rawStringSize = size;
            m_rawString = new char[m_rawStringSize];
        }

        void deallocate() {
            if (m_rawString != nullptr) {
                delete[] m_rawString;
                m_rawStringSize = 0;
            }
        }
    };

    const char* StringData::EMPTY_STRING = "";

    String::String() {
        m_sharedData = SharedData<StringData>::create();
    }

    String::String(const char* cString) {
        m_sharedData = SharedData<StringData>::create(cString);
    }

    String::String(const String& other) {
        m_sharedData = other.m_sharedData->makeRef();
    }

    String::String(SharedData<StringData>* sharedData) {
        m_sharedData = sharedData;
    }

    int String::compare(const String& l, const String& r) {
        return raw_string::compareCaseInsensitive(l.rawString(), r.rawString());
    }

    String::~String() {
        if (m_sharedData->derefAndCheckDelete())
            delete m_sharedData;
    }

    String& String::operator =(const char* cString) {
        if (m_sharedData->derefAndCheckDelete())
            delete m_sharedData;
        m_sharedData = SharedData<StringData>::create(cString);
        return *this;
    }

    String& String::operator =(const String& other) {
        if (m_sharedData->derefAndCheckDelete())
            delete m_sharedData;
        m_sharedData = other.m_sharedData->makeRef();
        return *this;
    }

    const char* String::rawString() const {
        return m_sharedData->data->m_rawString;
    }

    String operator +(const String& l, const String& r) {
        auto sharedData = SharedData<StringData>::create(l.rawString());
        sharedData->data->append(r.rawString());
        return String(sharedData);
    }

    bool operator <(const String& l, const String& r) {
        return String::compare(l, r) < 0;
    }

    bool operator <=(const String& l, const String& r) {
        return String::compare(l, r) <= 0;
    }

    bool operator >(const String& l, const String& r) {
        return String::compare(l, r) > 0;
    }

    bool operator >=(const String& l, const String& r) {
        return String::compare(l, r) >= 0;
    }

    bool operator ==(const String& l, const String& r) {
        return String::compare(l, r) == 0;
    }

    bool operator !=(const String& l, const String& r) {
        return String::compare(l, r) != 0;
    }
}
