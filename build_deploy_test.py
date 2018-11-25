from eosfactory.eosf import *

contract = ContractBuilder("signature")
contract.build()
reset()
create_master_account("master")
create_account("host", master)
contract = Contract(host, contract.path())
contract.deploy()
contract.push_action("addsignature", {"dpi": "3001973810101"}, permission=tortola)