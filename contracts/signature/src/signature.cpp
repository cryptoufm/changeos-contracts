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

class signature : public eosio::contract {

    public:
        using contract::contract;

        [[eosio::action]]
        void addsignature( string dpi ) {
            print( "DPI received: ", dpi );
            verifydpi(dpi);
        }

        bool verifydpi( string dpi ) {
            logger_info( "debug dpi: ", dpi);
            return true;
       }





};

EOSIO_ABI( signature, (addsignature) )
