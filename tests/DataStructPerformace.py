from operator import add
from client_sdk_python import Web3, HTTPProvider, WebsocketProvider
from client_sdk_python.eth import PlatON
from client_sdk_python import utils
from client_sdk_python.utils import contracts

import json

ContractAddr = 'lat1au3vujt9867xyln7nmpcjm6l32jvdycyegf29h'

clientAccount = 'lat1hszgljlqnlly6hxcneq6v2vdnaj9hfvm7m7ccz'
devIP = 'http://47.241.69.26:6789'

ABI_filepath = './PlatON/config/WasmDataStruct.abi.json'

ID_Slice = 25
Slice_Range = 8
MaxID = 1000000

def CreateDataForMap():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    for i in range(Slice_Range):
        tx_receipt = hello.functions.CreateDataForMap(i * ID_Slice, (i + 1) * ID_Slice).transact({'from':clientAccount,'gas':9000000})
        receipt_info = platon.waitForTransactionReceipt(tx_receipt)
        print('Create ', ID_Slice, 'data for db::Map. Status: ', receipt_info['status'], '. CumulativeGasUsed: ', receipt_info['cumulativeGasUsed'])


def CreateDataForST():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    for i in range(Slice_Range):
        tx_receipt = hello.functions.CreateDataForST(i * ID_Slice, (i + 1) * ID_Slice).transact({'from':clientAccount,'gas':9000000})
        receipt_info = platon.waitForTransactionReceipt(tx_receipt)
        print('Create ', ID_Slice, 'data for StorageType. Status: ', receipt_info['status'], '. cumulativeGasUsed: ', receipt_info['cumulativeGasUsed'])


def CreateDataForMI():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    for i in range(Slice_Range):
        tx_receipt = hello.functions.CreateDataForMI(i * ID_Slice, (i + 1) * ID_Slice).transact({'from':clientAccount,'gas':9000000})
        receipt_info = platon.waitForTransactionReceipt(tx_receipt)
        print('Create ', ID_Slice, 'data for db::Multi_Index. Status: ', receipt_info['status'], '. cumulativeGasUsed: ', receipt_info['cumulativeGasUsed'])

    
def getItemDescription():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    print(hello.functions.getUserFromMap(450).call())
    print(hello.functions.getUserFromTable_ID(100).call())
    print(hello.functions.getUserFromStorageType(150).call())


def clear():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    tx_receipt = hello.functions.BatchClear(750).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print(receipt_info)


def Add():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    tx_receipt = hello.functions.AddUserForMap([MaxID, 'jason', 'Hello']).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('AddUserForMap: ', receipt_info['cumulativeGasUsed'])

    tx_receipt = hello.functions.AddUserForST([MaxID, 'jason', 'Hello']).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('AddUserForST: ', receipt_info['cumulativeGasUsed'])

    tx_receipt = hello.functions.AddUserForMI([MaxID, 'jason', 'Hello']).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('AddUserForMI: ', receipt_info['cumulativeGasUsed'])


def Modify():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    tx_receipt = hello.functions.ModifyForMap([MaxID, 'jason', 'World']).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('ModifyForMap: ', receipt_info['cumulativeGasUsed'])

    tx_receipt = hello.functions.ModifyForST([MaxID, 'jason', 'World']).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('ModifyForST: ', receipt_info['cumulativeGasUsed'])

    tx_receipt = hello.functions.ModifyForMI([MaxID, 'jason', 'World']).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('ModifyForMI: ', receipt_info['cumulativeGasUsed'])


def Erase():
    fp = open(ABI_filepath)
    Contract_abi = json.load(fp)
    w3 = Web3(HTTPProvider(devIP))
    platon = PlatON(w3)

    hello = platon.wasmcontract(address=ContractAddr, abi=Contract_abi, vmtype=1)

    tx_receipt = hello.functions.EraseForMap(MaxID).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('EraseUserForMap: ', receipt_info['cumulativeGasUsed'])

    tx_receipt = hello.functions.EraseForST(MaxID).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('EraseUserForST: ', receipt_info['cumulativeGasUsed'])

    tx_receipt = hello.functions.EraseForMI(MaxID).transact({'from':clientAccount,'gas':9000000})
    receipt_info = platon.waitForTransactionReceipt(tx_receipt)
    print('EraseUserForMI: ', receipt_info['cumulativeGasUsed'])


#CreateDataForMap()
#CreateDataForST()
#CreateDataForMI()
#getItemDescription()
#clear()
#Add()
#Modify()
#Erase()
