#pragma once

#include "../../FLCoreDefs.hpp"

#include "RoomData.hpp"

enum class TransactionType
{
    Sell = 0,
    Buy = 1
};

struct IMPORT MarketGoodInfo
{
    MarketGoodInfo();
    MarketGoodInfo& operator=(const MarketGoodInfo&);

  public:
    unsigned goodId;
    f32 price;
    int min;
    int stock;
    TransactionType transType;
    f32 rank;
    f32 rep;
    // int quantity; Those two fields are not actually there? Where'd we get those from?
    // f32 scale;
};

class IMPORT BaseData
{
  public:
    BaseData(const BaseData&);
    BaseData();
    ~BaseData();
    BaseData& operator=(const BaseData&);
    u32 get_base_id() const;
    // const st6::list<class RoomData*>* get_const_room_data_list() const;
    // const st6::map<u32, struct MarketGoodInfo, st6::less<u32>, st6::allocator<MarketGoodInfo>>* get_market() const;
    // st6::list<RoomData*>* get_room_data_list();
    //  commented out since they'd fail on the account of them being defined as 'std' in the game binaries. Use the fields below directly instead.
    f32 get_price_variance() const;
    f32 get_ship_repair_cost() const;
    u32 get_start_location() const;
    void read_from_ini(const char*, u32);
    void set_market_good(u32, int, int, TransactionType, f32, f32, f32);

  private:
    void read_Base_block(class INI_Reader*);
    void read_Room_block(INI_Reader*);

  public:
    unsigned dunno;
    f32 startRoom;
    f32 priceVariance;
    f32 shipRepairCost;
    st6::map<Id, MarketGoodInfo> marketMap;
    st6::list<RoomData*> roomData;
};

class IMPORT BaseDataList
{
  public:
    BaseDataList(const BaseDataList&);
    BaseDataList();
    ~BaseDataList();
    BaseDataList& operator=(const BaseDataList&);
    BaseData* get_base_data(u32) const;
    st6::list<BaseData*>* get_base_data_list();
    const st6::list<BaseData*>* get_const_base_data_list() const;
    RoomData* get_room_data(u32) const;
    RoomData* get_unloaded_room_data(u32) const;
    void load();
    void load_market_data(const char*);

  public:
    u8 data[OBJECT_DATA_SIZE];
};

// Common functions

IMPORT void BaseDataList_destroy();
IMPORT BaseDataList* BaseDataList_get();
IMPORT void BaseDataList_load();
IMPORT void BaseDataList_load_market_data(const char*);
