// ArduinoNvs.cpp

// Copyright (c) 2018 Sinai RnD
// Copyright (c) 2016-2017 TridentTD

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "ArduinoNvs.h"

ArduinoNvs::ArduinoNvs()
{
}

bool ArduinoNvs::write(String key, const uint8_t *buf, uint32_t len)
{
  File file = SPIFFS.open("/" + key, FILE_WRITE);
  if (!file)
  {
    DEBUG_PRINTF("There was an error opening the file for writing");
    return false;
  }
  file.write(buf, len);
  file.flush();
  file.close();
  return true;
}

bool ArduinoNvs::read(String key, uint8_t *buf, uint32_t len, bool read_all , uint32_t * ret)
{
  File file = SPIFFS.open("/" + key, FILE_READ);
  if (!file)
  {
    DEBUG_PRINTF("There was an error opening the file for reading");
    return false;
  }
  int size = len;
  if (read_all)
  {
    if (len < file.size())
    {
      DEBUG_PRINTF("buffer too small");
      return false;
    }
    size = file.size();
  }
  *ret = file.read(buf, size);
  file.close();
  return true;
}

bool ArduinoNvs::begin(String namespaceNvs)
{
  if (!SPIFFS.begin(true))
  {
    DEBUG_PRINTF("An Error has occurred while mounting SPIFFS");
    return false;
  }
  return true;
}

void ArduinoNvs::close()
{
  SPIFFS.end();
}

bool ArduinoNvs::eraseAll(bool forceCommit)
{
  return SPIFFS.format();
}

bool ArduinoNvs::erase(String key, bool forceCommit)
{
  return SPIFFS.remove("/" + key);
}

bool ArduinoNvs::commit()
{
  return true;
}

bool ArduinoNvs::setInt(String key, uint8_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 1);
}

bool ArduinoNvs::setInt(String key, int16_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 2);
}

bool ArduinoNvs::setInt(String key, uint16_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 2);
}

bool ArduinoNvs::setInt(String key, int32_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 4);
}

bool ArduinoNvs::setInt(String key, uint32_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 4);
}
bool ArduinoNvs::setInt(String key, int64_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 8);
}

bool ArduinoNvs::setInt(String key, uint64_t value, bool forceCommit)
{
  return write(key, (const uint8_t *)&value, 8);
}

bool ArduinoNvs::setString(String key, String value, bool forceCommit)
{
  return write(key, (const uint8_t *)value.c_str(), value.length());
}

bool ArduinoNvs::setBlob(String key, uint8_t *blob, size_t length, bool forceCommit)
{
  return write(key, blob, length);
}

bool ArduinoNvs::setBlob(String key, std::vector<uint8_t> &blob, bool forceCommit)
{
  return write(key, (const uint8_t *)&blob[0], blob.size());
}

int64_t ArduinoNvs::getInt(String key)
{
  uint32_t ret = 0;
  uint8_t buf[8] = {0};
  read(key, buf, 8, true , &ret);
  int64_t *n = (int64_t *)buf;
  return *n;
}

bool ArduinoNvs::getBlob(String key, uint8_t *blob, size_t length)
{
  uint32_t ret = 0;
  return read(key, blob, length, true , &ret);
}

bool ArduinoNvs::getBlob(String key, std::vector<uint8_t> &blob)
{
  uint32_t ret = 0;
  return read(key, &blob[0], blob.size(), true , &ret);
}

std::vector<uint8_t> ArduinoNvs::getBlob(String key)
{
  std::vector<uint8_t> res;
  bool ok = getBlob(key, res);
  if (!ok)
    res.clear();
  return res;
}

bool ArduinoNvs::setFloat(String key, float value, bool forceCommit)
{
  return setBlob(key, (uint8_t *)&value, sizeof(float), forceCommit);
}

float ArduinoNvs::getFloat(String key)
{
  std::vector<uint8_t> res(sizeof(float));
  if (!getBlob(key, res))
    return 0;
  return *(float *)(&res[0]);
}

bool ArduinoNvs::getString(String key, String &res)
{   
  uint32_t ret = 0;
  uint8_t buf[STR_BUFFER_SIZE]; 
  memset(buf , 0 , STR_BUFFER_SIZE);
  read(key , buf , STR_BUFFER_SIZE , true ,  &ret);
  res = String((const char*)buf);
  return true;
}
String ArduinoNvs::getString(String key)
{
  String str;
  getString(key , str);
  return str;
}

ArduinoNvs NVS;
