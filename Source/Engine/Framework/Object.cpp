#include "Object.h"

namespace nc
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
		READ_DATA(value, active);
	}
}