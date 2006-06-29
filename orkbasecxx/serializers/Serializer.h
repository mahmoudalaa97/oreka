/*
 * Oreka -- A media capture and retrieval platform
 * 
 * Copyright (C) 2005, orecx LLC
 *
 * http://www.orecx.com
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License.
 * Please refer to http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#pragma warning( disable: 4786 ) // disables truncated symbols in browse-info warning

#include "dll.h"
#include "OrkBase.h"
#include <map>
#include <list>
#include "boost/shared_ptr.hpp"
#include "StdString.h"

typedef int (*StringToEnumFunction)(CStdString&);
typedef CStdString (*EnumToStringFunction)(int);

class Object;

/** Base class for serializing Objects.
*/
class DLL_IMPORT_EXPORT_ORKBASE Serializer
{
public:
	Serializer(Object* object);

	void IntValue(const char* key, int& value, bool required = false);
	void DoubleValue(const char* key, double& value, bool required = false);
	void StringValue(const char* key, CStdString& value, bool required = false);
	void BoolValue(const char* key, bool& value, bool required = false);
	void EnumValue(const char* key, int& value, StringToEnumFunction, EnumToStringFunction, bool required = false);
	virtual void ObjectValue(const char* key, Object& value, bool required = false) = 0;
	void CsvValue(const char* key, std::list<CStdString>& value, bool required = false);
	void DateValue(const char* key, time_t& value, bool required = false);

	void AddInt(const char* key, int value);
	void AddDouble(const char* key, double value);
	void AddBool(const char* key, bool value);
	void AddEnum(const char* key, int value, EnumToStringFunction);
	void AddCsv(const char* key,  std::list<CStdString>& value);
	void AddDate(const char* key, time_t value);
	virtual void AddString(const char* key, CStdString& value) = 0;

	void GetInt(const char* key, int& value, bool required = false);
	void GetDouble(const char* key, double& value, bool required = false);
	void GetBool(const char* key, bool& value, bool required = false);
	void GetEnum(const char* key, int& value, StringToEnumFunction, bool required = false);
	void GetCsv(const char* key,  std::list<CStdString>& value, bool required = false);
	void GetDate(const char* key, time_t& value, bool required = false);
	virtual void GetString(const char* key, CStdString& value, bool required = false) = 0;

protected:

	Object* m_object;
	bool m_deSerialize;
};

typedef boost::shared_ptr<Serializer> SerializerRef;

/** Base class for all Key-Value pair based serializers.
*/
class DLL_IMPORT_EXPORT_ORKBASE KeyValueSerializer : public Serializer
{
public:
	KeyValueSerializer(Object* object) : Serializer(object), m_numParams(0){};

	void ObjectValue(const char* key, Object& value, bool required = false);

	void GetString(const char* key, CStdString& value, bool required = false);

protected:
	int m_numParams;
	std::map<CStdString, CStdString> m_map;
};

#endif

