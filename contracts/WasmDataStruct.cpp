#include "WasmDataStruct.h"

void WasmDataStruct::init(){
	
}

void WasmDataStruct::AddUser(const UserDefinedData& udd){
	_mUserMap[udd.uID] = udd;
	_mUser_Data.self()[udd.uID] = udd;

	_mUser_table.emplace([&](auto& userTable) {
		userTable = udd;
		});
}

void WasmDataStruct::ModifyUserInfo(const UserDefinedData& udd){
	//_mUserMap
	if (_mUserMap.contains(udd.uID))
	{
		// _mUserMap[udd.uID] = udd;
		auto mapItem = &_mUserMap[udd.uID];
		*mapItem = udd;
	}

	//_mUser_Data
	auto udItr = _mUser_Data.self().find(udd.uID);
	if (udItr != _mUser_Data.self().end())
	{
		udItr->second = udd;
	}

	//_mUser_table
	auto uTableItr = _mUser_table.find<"id"_n>(udd.uID);
	if (uTableItr != _mUser_table.cend())
	{
		_mUser_table.modify(uTableItr, [&](auto& userData) {
			// userData = udd;
			// userData.uName = udd.uName;
			// keys cannot be changed
			userData.uContent = udd.uContent;
			auto tmpName = userData.uName;
			auto tmpID = userData.uID;

			userData.uName = "haha";
			userData.uID = 1100;

			userData.uName = tmpName;
			userData.uID = tmpID;
		});
	}
	// auto uTableItrs = _mUser_table.get_index<"name"_n>();
	// auto itemItr = uTableItrs.cbegin(udd.uName); 
	// if (itemItr != uTableItrs.cend(udd.uName))
	// {
	// 	uTableItrs.modify(itemItr, [&](auto& userData){
	// 		userData = udd;
	// 		userData.uID = 4;
	// 	});
	// }
}

void WasmDataStruct::UserErase(const platon::u128& uID){
	//_mUserMap
	if (_mUserMap.contains(uID))
	{
		_mUserMap.erase(uID);
	}

	//_mUser_Data
	auto udItr = _mUser_Data.self().find(uID);
	if (udItr != _mUser_Data.self().end())
	{
		_mUser_Data.self().erase(udItr);
	}

	//_mUser_table
	auto uTableItr = _mUser_table.find<"id"_n>(uID);
	if (uTableItr != _mUser_table.cend())
	{
		_mUser_table.erase(uTableItr);
	}
}

void WasmDataStruct::Clear(){
	//the clear of db::Map and db::MultiIndex are Some trouble
	std::vector<platon::u128> idVec;
	for (auto usItr = _mUser_Data.self().begin(); usItr != _mUser_Data.self().end(); ++usItr)
	{
		idVec.push_back(usItr->first);
	}

	//normal map
	_mUser_Data.self().clear();

	//db::Map
	for (auto idItr = idVec.begin(); idItr != idVec.end(); ++idItr)
	{
		_mUserMap.erase(*idItr);
	}

	//db::MultiIndex
	auto tableItr = _mUser_table.cbegin();
	while (tableItr != _mUser_table.cend())
	{
		auto tempItr = tableItr;
		++tableItr;
		
		_mUser_table.erase(tempItr);
	}
}

std::vector<UserDefinedData> WasmDataStruct::getUserFromTable_ID(const platon::u128& uID){
	std::vector<UserDefinedData> udVec;

	auto uTableItr = _mUser_table.find<"id"_n>(uID);
	if (uTableItr != _mUser_table.cend())
	{
		
		udVec.push_back(*uTableItr);
	}

	//if not found, return []
	return udVec;
}

std::vector<UserDefinedData> WasmDataStruct::getUserFromTable_Name(const std::string& uName){
	std::vector<UserDefinedData> udVec;
	//Here's where it gets more confusing, maybe set parameters in get_index is better
	auto normalIndexes = _mUser_table.get_index<"name"_n>();
	for (auto itemItr = normalIndexes.cbegin(uName); itemItr != normalIndexes.cend(uName); ++itemItr)
	{
		udVec.push_back(*itemItr);
	}

	return udVec;
}

std::vector<UserDefinedData> WasmDataStruct::getUserFromMap(const platon::u128& uID){
	std::vector<UserDefinedData> udVec;

	if (_mUserMap.contains(uID))
	{
		udVec.push_back(_mUserMap[uID]);
	}

	return udVec;
}

std::vector<UserDefinedData> WasmDataStruct::getUserFromStorageType(const platon::u128& uID){
	std::vector<UserDefinedData> udVec;

	auto udItr = _mUser_Data.self().find(uID);
	if (udItr != _mUser_Data.self().end())
	{
		udVec.push_back(udItr->second);
	}

	return udVec;
}

// Performace Evaluation
void WasmDataStruct::CreateDataForMap(const platon::u128& MinID, const platon::u128& MaxID)
{
	for (auto i = MinID; i < MaxID; ++i)
	{
		UserDefinedData udd;
		udd.uID = i;
		udd.uName = std::to_string(i);
		udd.uContent = "Hello";

		_mUserMap[udd.uID] = udd;
	}
}

void WasmDataStruct::CreateDataForST(const platon::u128& MinID, const platon::u128& MaxID)
{
	for (auto i = MinID; i < MaxID; ++i)
	{
		UserDefinedData udd;
		udd.uID = i;
		udd.uName = std::to_string(i);
		udd.uContent = "Hello";

		_mUser_Data.self()[udd.uID] = udd;
	}
}

void WasmDataStruct::CreateDataForMI(const platon::u128& MinID, const platon::u128& MaxID)
{
	for (auto i = MinID; i < MaxID; ++i)
	{
		UserDefinedData udd;
		udd.uID = i;
		udd.uName = std::to_string(i);
		udd.uContent = "Hello";

		_mUser_table.emplace([&](auto& userTable) {
			userTable = udd;
			});
	}
}

void WasmDataStruct::AddUserForMap(const UserDefinedData& udd)
{
	_mUserMap[udd.uID] = udd;
}

void WasmDataStruct::AddUserForST(const UserDefinedData& udd)
{
	_mUser_Data.self()[udd.uID] = udd;
}

void WasmDataStruct::AddUserForMI(const UserDefinedData& udd)
{
	_mUser_table.emplace([&](auto& userTable) {
		userTable = udd;
		});
}

void WasmDataStruct::ModifyForMap(const UserDefinedData& udd)
{
	//_mUserMap
	if (_mUserMap.contains(udd.uID))
	{
		_mUserMap[udd.uID] = udd;
	}
}

void WasmDataStruct::ModifyForST(const UserDefinedData& udd)
{
	//_mUser_Data
	auto udItr = _mUser_Data.self().find(udd.uID);
	if (udItr != _mUser_Data.self().end())
	{
		udItr->second = udd;
	}
}

void WasmDataStruct::ModifyForMI(const UserDefinedData& udd)
{
	//_mUser_table
	auto uTableItr = _mUser_table.find<"id"_n>(udd.uID);
	if (uTableItr != _mUser_table.cend())
	{
		_mUser_table.modify(uTableItr, [&](auto& userData) {
			userData = udd;
			});
	}
}

void WasmDataStruct::EraseForMap(const platon::u128& uID){
	//_mUserMap
	if (_mUserMap.contains(uID))
	{
		_mUserMap.erase(uID);
	}
}

void WasmDataStruct::EraseForST(const platon::u128& uID){
	//_mUser_Data
	auto udItr = _mUser_Data.self().find(uID);
	if (udItr != _mUser_Data.self().end())
	{
		_mUser_Data.self().erase(udItr);
	}
}

void WasmDataStruct::EraseForMI(const platon::u128& uID){
	//_mUser_table
	auto uTableItr = _mUser_table.find<"id"_n>(uID);
	if (uTableItr != _mUser_table.cend())
	{
		_mUser_table.erase(uTableItr);
	}
}

std::string WasmDataStruct::getItemDescription()
{
	std::string output = "Items count: ";

	auto count = _mUser_Data.self().size();

	output += std::to_string(count);

	return output;
}

void WasmDataStruct::BatchClear(const platon::u128& MaxID){
	//normal map
	auto ST_Itr = _mUser_Data.self().begin();
	while (ST_Itr != _mUser_Data.self().end())
	{
		auto tempItr = ST_Itr;
		++ST_Itr;
		if (tempItr->first < MaxID)
		{
			_mUser_Data.self().erase(tempItr);
		}
	}

	//db::Map
	for (auto id = 0; id < MaxID; ++id)
	{
		if (_mUserMap.contains(id))
		{
			_mUserMap.erase(id);
		}
	}

	//db::MultiIndex
	// auto tableItr = _mUser_table.cbegin();
	// while (tableItr != _mUser_table.cend())
	// {
	// 	if (tableItr->uID < MaxID)
	// 	{
	// 		auto tempItr = tableItr;
	// 		_mUser_table.erase(tempItr);
	// 	}

	// 	++tableItr;
	// }

	for (auto id = 0; id < MaxID; ++id)
	{
		auto uTableItr = _mUser_table.find<"id"_n>(id);
		if (uTableItr != _mUser_table.cend())
		{
			_mUser_table.erase(uTableItr);
		}
	}
}
