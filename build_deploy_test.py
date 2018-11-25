from eosfactory.eosf import *


contract = ContractBuilder("referendum")

contract.build()
reset()
create_master_account("master")
create_account("host", master)
contract = Contract(host, contract.path())
contract.deploy()

print("----ContractTest----")

contract.push_action("insert", {"citizen_uid": "3001973810101", "volunteer_id": "JRBAGUR", "image_hash": "QmdodXR3WWQGxmUmQsZy9PjuzYuUwAiEgCMif92ChLq2sJ"}, permission=host)
#contract.push_action("insert", {"citizen_uid": "3001973810101", "volunteer_id": "JUANRO", "image_hash": "QmdodXR3Zy9PjuzYuUwAiEgCMif92ChWWQGxmUmQsLq2sJ"}, permission=host)
contract.push_action("insert", {"citizen_uid": "3003911290101", "volunteer_id": "JRBAGUR", "image_hash": "QmdodXR3WWQGxmUmQsZy9PjuzYuUwAiEgCMif92ChLq2sJ"}, permission=host)

#contract.push_action("retrieve", {"citizen_uid": "3001973810101"} , permission=host)

#contract.push_action("allvotes", {}, permission=host)
print("----/ContractTest----")

host.table("petition", "3001973810101")
host.table("petition")