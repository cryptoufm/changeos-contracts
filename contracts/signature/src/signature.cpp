#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <map>
#include <iterator>
#include <string>

#define DEBUG

#include "logger.hpp"
#include "signature.hpp"

using namespace eosio;
using namespace std;

class Signature {
    public:
        Signature() {}
        Signature(std::string volunteerid, std::string imagehash) : volunteerid(volunteerid), imagehash(imagehash) {}
        std::string volunteerid;
        std::string imagehash; 
};


class vote : public eosio::contract {

    public:
        using contract::contract;

        std::map<std::string, Signature> registry; 

        [[eosio::action]]
        void addsignature( string volunteerid, string citizenuid, string imagehash ) {
            print( "DPI received: ", volunteerid, citizenuid, imagehash );
            if (verifydpi(citizenuid)) {
                logger_info( "SUCCESS: DPI added: ", citizenuid);
                registry.insert(std::map<std::string, Signature>::value_type(citizenuid, Signature(volunteerid,imagehash)));
            } 
            else {
                logger_info( "FAILED: DPI not added: ", citizenuid);
            }
        }

        bool verifydpi( string dpi ) {
            print( "DPI received in VERIFYDPI" );

            std::map<std::string, Signature>::iterator found; 
            found = registry.find(dpi);
            if (found != registry.end()) {
                return true;
            }
            else {
                return false;
            }
       }

};

EOSIO_ABI( vote, (addsignature) )
