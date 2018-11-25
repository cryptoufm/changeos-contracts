from eosfactory.eosf import *

contract = ContractBuilder("signature")
contract.build()
reset()
create_master_account("master")
create_account("host", master)
contract = Contract(host, contract.path())
contract.deploy()

contract.push_action("insert", {"citizen_uid": "3001973810101", "volunteer_id": "JRBAGUR", "image_hash": "QmdodXR3WWQGxmUmQsZy9PjuzYuUwAiEgCMif92ChLq2sJ"}, permission=host)
contract.push_action("insert", {"citizen_uid": "3001973810101", "volunteer_id": "JUANRO", "image_hash": "xmUmQzYuU3WWQGxmUmQQmdodXR3WWQGsZy9Pjuif92ChLq2sJ"}, permission=host)