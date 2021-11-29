#pragma once

#include <platon/platon.hpp>
#include <string>
#include <vector>

struct UserDefinedData
{
	platon::u128	uID;
	std::string		uName;

	std::string		uContent;

	PLATON_SERIALIZE(UserDefinedData, (uID)(uName)(uContent))

	platon::u128 UserID() const { return uID; }
	std::string UserName() const { return uName; }
};

class WasmDataStruct
{
	//map
	platon::db::Map<"UserDataMap"_n, platon::u128, UserDefinedData> _mUserMap;

	//multiIndex table
	platon::db::MultiIndex<
		"UserTable"_n, UserDefinedData,
		platon::db::IndexedBy<"id"_n, platon::db::IndexMemberFun<UserDefinedData, platon::u128, &UserDefinedData::UserID,
		platon::db::IndexType::UniqueIndex>>,
		platon::db::IndexedBy<"name"_n, platon::db::IndexMemberFun<UserDefinedData, std::string, &UserDefinedData::UserName,
		platon::db::IndexType::NormalIndex>>>
		
		_mUser_table;

	//StorageType
	platon::StorageType<"UserData"_n, std::map<platon::u128, UserDefinedData>>		_mUser_Data;

public:
	ACTION void init();

	ACTION void AddUser(const UserDefinedData& udd);

	ACTION void ModifyUserInfo(const UserDefinedData& udd);

	ACTION void UserErase(const platon::u128& uID);

	ACTION void Clear();

	CONST std::vector<UserDefinedData> getUserFromTable_ID(const platon::u128& uID);
	CONST std::vector<UserDefinedData> getUserFromTable_Name(const std::string& uName);

	CONST std::vector<UserDefinedData> getUserFromMap(const platon::u128& uID);

	CONST std::vector<UserDefinedData> getUserFromStorageType(const platon::u128& uID);

	// Performance Evaluation
	ACTION void CreateData(const platon::u128& MaxID);

	ACTION void AddUserForMap(const UserDefinedData& udd);
	ACTION void AddUserForST(const UserDefinedData& udd);
	ACTION void AddUserForMI(const UserDefinedData& udd);

	ACTION void ModifyForMap(const UserDefinedData& udd);
	ACTION void ModifyForST(const UserDefinedData& udd);
	ACTION void ModifyForMI(const UserDefinedData& udd);

	ACTION void EraseForMap(const platon::u128& uID);
	ACTION void EraseForST(const platon::u128& uID);
	ACTION void EraseForMI(const platon::u128& uID);
};

PLATON_DISPATCH(WasmDataStruct, (init)(AddUser)(ModifyUserInfo)(UserErase)(Clear)(getUserFromTable_ID)(getUserFromTable_Name)(getUserFromMap)(getUserFromStorageType))
