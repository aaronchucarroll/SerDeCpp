#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include "../include/pack109.hpp"

vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE); //pushes true flag
  } else {
    bytes.push_back(PACK109_FALSE); // pushes false flag
  }
  return bytes;
}

bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) { // size error checking
     throw;
  }
  if (bytes[0] == PACK109_TRUE) { // identifier checking
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }
}

vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8); // push identifier
  bytes.push_back(item); // push value
  return bytes;
}

u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) { // size error checking
    throw;
  }
  if (bytes[0] == PACK109_U8) {
    return bytes[1];
  } else {
    throw;
  }
}

vec pack109::serialize(u32 item){
  vec bytes;
  int num[4]; // array of bytes
  num[0] = (item >> 24) & 0xFF; // bit shifting to extract each byte of u32
  num[1] = (item >> 16) & 0xFF;
  num[2] = (item >> 8) & 0xFF;
  num[3] = item & 0xFF;
  bytes.push_back(PACK109_U32);
  for (int i = 0; i < 4; i++){
    bytes.push_back(num[i]); // pushing in each byte
  }
  return bytes;
}

u32 pack109::deserialize_u32(vec bytes){
  if (bytes.size() < 5){ // size error checking
    throw;
  }
  if (bytes[0] == PACK109_U32){
    u32 ret = (bytes[1] << 24) | (bytes[2] << 16) | (bytes[3] << 8) | bytes[4]; // forming a u32 from the bytes of the array
    return ret;
  }else{
    throw;
  }
}

vec pack109::serialize(u64 item){
  vec bytes;
  int num[8];
  num[0] = (item >> 56) & 0xFF; // bit shifting to separate 8 bytes
  num[1] = (item >> 48) & 0xFF;
  num[2] = (item >> 40) & 0xFF;
  num[3] = (item >> 32) & 0xFF;
  num[4] = (item >> 24) & 0xFF;
  num[5] = (item >> 16) & 0xFF;
  num[6] = (item >> 8) & 0xFF;
  num[7] = item & 0xFF;
  bytes.push_back(PACK109_U64); 
  for (int i = 0; i < 8; i++){
    bytes.push_back(num[i]); // pushing each byte
  }
  return bytes;
}

u64 pack109::deserialize_u64(vec bytes){
  if (bytes.size() < 9){
    throw;
  }
  u64 num[8];
  if (bytes[0] == PACK109_U64){
   for (int i = 0; i < 8; i++){
      num[i] = bytes[i+1];
      num[i] = num[i] << (7 - i) * 8; // bit shifting and assigning to byte array
    }
    u64 ret;
    ret = num[0] + num[1] + num[2] + num[3] + num[4] + num[5] + num[6] + num[7]; // forming a u64 out of the bytes
    return ret;
  }else{
    throw;
  }
}

vec pack109::serialize(i8 item){
  vec bytes;
  bytes.push_back(PACK109_I8); // push identifier
  bytes.push_back(item); // push value
  return bytes;
}

i8 pack109::deserialize_i8(vec bytes){
  if (bytes.size() < 2){
    throw;
  }
  if (bytes[0] == PACK109_I8){
    return bytes[1]; // returning the i8 value
  }else{
    throw;
  }
}

vec pack109::serialize(i32 item){
  vec bytes;
  int num[4];
  num[0] = (item >> 24) & 0xFF;
  num[1] = (item >> 16) & 0xFF; // bit shifting to separate four bytes
  num[2] = (item >> 8) & 0xFF;
  num[3] = item & 0xFF;
  bytes.push_back(PACK109_I32);
  for (int i = 0; i < 4; i++){
    bytes.push_back(num[i]); // pushing each byte
  }
  return bytes;
}

i32 pack109::deserialize_i32(vec bytes){
  if (bytes.size() < 5){
    throw;
  }
  if (bytes[0] == PACK109_I32){
    i32 ret = (bytes[1] << 24) | (bytes[2] << 16) | (bytes[3] << 8) | bytes[4]; // bit shifting to stagger the bytes. Forming an i32 out of the four bytes
    return ret;
  }else{
    throw;
  }
}

vec pack109::serialize(i64 item) {
  vec bytes;
  int num[8];
  for (int i = 0; i < 8; i++){
    num[i] = (item >> ((7 - i) * 8)) & 0xFF; //  bit shifting to separate 8 bytes
  }
  bytes.push_back(PACK109_I64);
  for(int i = 0; i < 8; i++){
    bytes.push_back(num[i]); // pushing each byte
  }
  return bytes;
}

i64 pack109::deserialize_i64(vec bytes) {
  if (bytes.size() < 9) { // size error checking
    throw;
  }
  i64 num[8];
  if (bytes[0] == PACK109_I64) {
    for (int i = 0; i < 8; i++){
      num[i] = bytes[i+1];
      num[i] = num[i] << (7-i) * 8; // bit shifting to stagger and assigning separated bytes to num array
    }
    i64 ret = num[0] + num[1] + num[2] + num[3] + num[4] + num[5] + num[6] + num[7]; // forming bytes into an i64
    return ret;
  } else {
    throw;
  }
}

vec pack109::serialize(f32 item) {
  vec bytes;
  bytes.push_back(PACK109_F32);
  u32 num = *(reinterpret_cast<u32*>(&item)); // casting the float bytes to a u32. reintepret_cast preserves the bytes without caring about the data type
  bytes.push_back(num >> 24); // bit shifting
  bytes.push_back(num >> 16);
  bytes.push_back(num >> 8);
  bytes.push_back(num);
  return bytes;
}

f32 pack109::deserialize_f32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  if (bytes[0] == PACK109_F32) {
    u32 num = (static_cast<u32>(bytes[1]) << 24) | (static_cast<u32>(bytes[2]) << 16) | (static_cast<u32>(bytes[3]) << 8) | (static_cast<u32>(bytes[4])); // must convert to 32 bit form
    f32 ret = *(reinterpret_cast<f32*>(&num)); // cast bytes back to float
    return ret;
  } else {
    throw;
  }
}

vec pack109::serialize(f64 item){
  vec bytes;
  bytes.push_back(PACK109_F64);
  u64 num = *(reinterpret_cast<u64*>(&item)); // casting float bytes to a u64, preserving the bytes.
  for (int i = 0; i < 8; i++){
    bytes.push_back(num >> ((7-i) * 8)); // pushing bytes into byte array
  }
  return bytes;
}

f64 pack109::deserialize_f64(vec bytes){
  if (bytes.size() < 9) {
    throw;
  }
  if (bytes[0] == PACK109_F64) {
    u64 num = (static_cast<u64>(bytes[1]) << 56) | (static_cast<u64>(bytes[2]) << 48) | (static_cast<u64>(bytes[3]) << 40) | (static_cast<u64>(bytes[4]) << 32) | (static_cast<u64>(bytes[5]) << 24) | (static_cast<u64>(bytes[6]) << 16) | (static_cast<u64>(bytes[7]) << 8) | (static_cast<u64>(bytes[8]));
    f64 ret = *(reinterpret_cast<f64*>(&num)); // repeat of f32. Casting bytes to u64s then casting u64 back to f64 form.
    return ret;
  } else {
    throw;
  }
}


vec pack109::serialize(string item) {
  vec bytes;
  if(item.size() <= 255){  // maximum s8 size
    bytes.push_back(PACK109_S8);
    bytes.push_back(item.size()); // store item size
    for(int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]); // push each char
    }
  }else{
    bytes.push_back(PACK109_S16); // surpasses maximum s8 size
    bytes.push_back((item.size() >> 8) & 0xFF);  // push in the size as two bytes
    bytes.push_back(item.size() & 0xFF);
    for(int i = 0; i < item.size(); i++){
      bytes.push_back((int)(item[i])); // push each char
    }
  }
  return bytes;
}

string pack109::deserialize_string(vec bytes) {
  if (bytes.size() < 3) {
    throw;
  }
  if (bytes[0] == PACK109_S8) {
    string ret_string = "";
    for (int i = 1; i <= bytes[1]; i++){
      ret_string += static_cast<char>(bytes[i+1]); // add each char in order to return string
    }
    return ret_string;
  } else if (bytes[0] == PACK109_S16) {
    string ret_string = "";
    int num_int = (bytes[1] <<8) | (bytes[2]); // forming the two byte number into a single int
    for(int i = 2; i < num_int+2; i++){
      ret_string += static_cast<char>(bytes[i+1]); // add each char to return string
    }
    return ret_string;
  } else {
    throw;
  }
}

vec pack109::serialize(std::vector<u8> item){
  vec bytes;
  if (item.size() <= 255){ // maximum a8 size
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
    for (int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]); // simply push in each element
    }
  }else{
    bytes.push_back(PACK109_A16);
    bytes.push_back((item.size() >> 8) & 0xFF);
    bytes.push_back(item.size() & 0xFF); // represent size as two bytes
    for (int i = 0; i < item.size(); i++){
      bytes.push_back((int)item[i]);
    }
  }
  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes){
  std::vector<u8> ret_vec;
  if (bytes.size() < 3){
    throw;
  }
  if (bytes[0] == PACK109_A8){
    for (int i = 2; i < bytes.size(); i++){
      ret_vec.push_back(bytes[i]); // extract each element
    }
    return ret_vec;
  }else if (bytes[0] == PACK109_A16){
    string num = std::to_string(bytes[1]);
    num += std::to_string(bytes[2]);
    int numInt = std::stoi(num); // turn two-byte size into one int
    for (int i = 3; i < numInt; i++){
      ret_vec.push_back(bytes[i]); // extract each element
    }
    return ret_vec;
  }else{
    throw;
  }
}

vec pack109::serialize(std::vector<u64> item){
  vec bytes;
  if (item.size() <= 255){
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size());
    for (int i = 0; i < item.size(); i++){
      int num[8];
      num[0] = (item[i] >> 56) & 0xFF;
      num[1] = (item[i] >> 48) & 0xFF; // bit shifting to insert the u64 byte-by-byte
      num[2] = (item[i] >> 40) & 0xFF;
      num[3] = (item[i] >> 32) & 0xFF;
      num[4] = (item[i] >> 24) & 0xFF;
      num[5] = (item[i] >> 16) & 0xFF;
      num[6] = (item[i] >> 8) & 0xFF;
      num[7] = item[i] & 0xFF;
      for (int i = 0; i < 8; i++){
        bytes.push_back(num[i]); // push in each byte
      }
    }
  }else{
    bytes.push_back(PACK109_A16);
    bytes.push_back((item.size() >> 8) & 0xFF);
    bytes.push_back(item.size() & 0xFF);
    for (int i = 0; i < item.size(); i++){
      u64 temp = item[i];
      vec intBytes = pack109::serialize(temp); // calls on another serialize. Maybe i could have done this at many other points
      for (int j = 1; i < intBytes.size(); j++){
        bytes.push_back(intBytes[j]); 
      }
    }
  }
  return bytes; 
}

std::vector<u64> pack109::deserialize_vec_u64(vec bytes){
  std::vector<u64> ret_vec;
  if (bytes.size() < 3){
    throw;
  }
  if (bytes[0] == PACK109_A8){
     for(int i = 2; i < bytes[1]*8; i+=8){
      u64 byte1 = bytes[0+i];
      byte1 = byte1 << 56;
      u64 byte2 = bytes[1+i];
      byte2 = byte2 << 48;
      u64 byte3 = bytes[2+i];
      byte3 = byte3 << 40;
      u64 byte4 = bytes[3+i];
      byte4 = byte4 << 32;
      u64 byte5 = bytes[4+i];
      byte5 = byte5 << 24;
      u64 byte6 = bytes[5+i]; // bit shifting to form a u64
      byte6 = byte6 << 16;
      u64 byte7 = bytes[6+i];
      byte7 = byte7 << 8;
      u64 byte8 = bytes[7+i];
      u64 num = (byte1) + (byte2) + (byte3) + (byte4) + (byte5) + (byte6) + (byte7) + (byte8);//concantenates bytes of each u64
      ret_vec.push_back(num);
    }
    return ret_vec;
  }else if(bytes[0] == PACK109_A16){
    string numString = "";
    numString += std::to_string(bytes[1]);
    numString += std::to_string(bytes[2]);
    f64 numInt = std::stoi(numString); // forming two-byte int to a single number
    for(int i = 3; i < bytes[1]*8; i+=8){
      u64 byte1 = bytes[0+i];
      byte1 = byte1 << 56;
      u64 byte2 = bytes[1+i];
      byte2 = byte2 << 48;
      u64 byte3 = bytes[2+i];
      byte3 = byte3 << 40;
      u64 byte4 = bytes[3+i];
      byte4 = byte4 << 32;
      u64 byte5 = bytes[4+i];
      byte5 = byte5 << 24;
      u64 byte6 = bytes[5+i];
      byte6 = byte6 << 16;
      u64 byte7 = bytes[6+i];
      byte7 = byte7 << 8;
      u64 byte8 = bytes[7+i];
      u64 num = (byte1) + (byte2) + (byte3) + (byte4) + (byte5) + (byte6) + (byte7) + (byte8); // forming a u64
      ret_vec.push_back(num); 
    }
    return ret_vec;
  }else{
    throw;
  }
}

vec pack109::serialize(std::vector<string> item){
  vec bytes;
  if (item.size() <= 255){
    bytes.push_back(PACK109_A8);
    bytes.push_back(item.size()); // insert num of items in vector
    for (int i = 0; i < item.size(); i++){
      if (item[i].size() <= 255){ // this whole section is string serialization (repeated from earlier)
        bytes.push_back(PACK109_S8);
        bytes.push_back(item[i].size());
        for (int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }else{
        bytes.push_back(PACK109_S16);
        bytes.push_back((item[i].size() >> 8) & 0xFF);
        bytes.push_back(item[i].size() & 0xFF);
        for (int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }
    }
  }else{
    bytes.push_back(PACK109_A16); 
    bytes.push_back((item.size() >> 8) & 0xFF);
    bytes.push_back(item.size() & 0xFF); // splitting into two-byte num
    for (int i = 0; i < item.size(); i++){
      if (item[i].size() <= 255){
        bytes.push_back(PACK109_S8);
        bytes.push_back(item[i].size());
        for (int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]); // inserting certain of character of certain indexed string
        }
      }else{
        bytes.push_back(PACK109_S16);
        bytes.push_back((item[i].size() >> 8) & 0xFF);
        bytes.push_back(item[i].size() & 0xFF);
        for (int j = 0; j < item[i].size(); j++){
          bytes.push_back((int)item[i][j]);
        }
      }
    }
  }
  return bytes;
}

vec pack109::serialize(struct Person item){ // most of the person serialization is hardcoded. i.e. inserting specific byte numbers and values. 
  vec bytes;
  if (sizeof(item) <= 40){ // sum of size of elements
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x01);
    bytes.push_back(PACK109_S8);
    string type = "Person"; // hardcoded
    bytes.push_back(type.size());
    for (int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x03); //size of term "age"
    bytes.push_back(PACK109_S8);
    type = "age";
    bytes.push_back(type.size());
    for (int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_U8); // pass in u8 flag
    bytes.push_back(item.age); // pass in u8 for age
    bytes.push_back(PACK109_S8); // for height flag
    type = "height";
    bytes.push_back(type.size());
    for (int i = 0; i < type.size(); i++){ // push in characters of "height"
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_F32);
    u32 num_f32 = *(reinterpret_cast<u32*>(&item.height));//pushing in height value
    bytes.push_back(num_f32 >> 24);
    bytes.push_back(num_f32 >> 16);
    bytes.push_back(num_f32 >> 8);
    bytes.push_back(num_f32);

    bytes.push_back(PACK109_S8);// pushing in name flag 
    type = "name"; 
    bytes.push_back(type.size());
    for (int i = 0; i < type.size(); i++){ // pushing in characters of "name"
      bytes.push_back(static_cast<char>(type[i]));
    }
    string itemObject = item.name;
    if ((itemObject).size() <= 255){ // serializing and pushing characters in name
      bytes.push_back(PACK109_S8);
      bytes.push_back((itemObject).size());
      for (int k = 0; k < itemObject.size(); k++){
        bytes.push_back(static_cast<char>(itemObject[k]));
      }
    }else{
      bytes.push_back(PACK109_S16);
      bytes.push_back(itemObject.size());
      for (int k = 0; k < itemObject.size(); k++){
        bytes.push_back(itemObject[k]);
      }
    }
  }else{ // repeat of entire if statement but with larger map
    bytes.push_back(PACK109_M16);
    bytes.push_back(0x01);
    bytes.push_back(PACK109_S8);
    string type = "Person";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x03);
    bytes.push_back(PACK109_S8);
    type = "age";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_U8);
    bytes.push_back(item.age);
    bytes.push_back(PACK109_S8);
    type = "height";
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    bytes.push_back(PACK109_F32);
    u32 num_f32 = *(reinterpret_cast<u32*>(&item.height));//pushing in height value
    bytes.push_back(num_f32 >> 24);
    bytes.push_back(num_f32 >> 16);
    bytes.push_back(num_f32 >> 8);
    bytes.push_back(num_f32);
    bytes.push_back(PACK109_S8);
    type = "name"; 
    bytes.push_back(type.size());
    for(int i = 0; i < type.size(); i++){
      bytes.push_back(type[i]);
    }
    string itemObj = item.name;
    if((itemObj).size() <= 255){ // pushing in string butes
      bytes.push_back(PACK109_S8);
      bytes.push_back((itemObj).size());
      for(int k = 0; k < itemObj.size(); k++){
        bytes.push_back(itemObj[k]);
      }
    }else{
      bytes.push_back(PACK109_S16);
      bytes.push_back((itemObj).size()); 
      for(int k = 0; k < itemObj.size(); k++){
        bytes.push_back(itemObj[k]);
      }
    }
  }
  return bytes;
}

struct Person pack109::deserialize_person(vec bytes){
  Person obj; // initializing a return object
  int pos = 0; // holds our current location in the vector
  if(bytes.size() < 15){
    throw;
  }
  if(bytes[pos] == PACK109_M8){
    pos += 2;
    if(bytes[pos] == PACK109_S8){
      string ret_string = ""; //forming a name string
      int name_len = bytes[3];
      for(int i = 0; i < name_len; i++){
        ret_string += std::to_string(bytes[i + 4]);
      }
      pos += name_len + 2; // advancing pos
      if(bytes[pos] == PACK109_M8){
        pos += 3;
        pos += bytes[pos]+1;
        if (bytes[pos] == PACK109_U8) { 
          obj.age = bytes[pos + 1]; // getting an age for return obj
          pos += 3;
          pos += bytes[pos]+1;
          if (bytes[pos] == PACK109_F32) {
            u32 u32_num = (static_cast<u32>(bytes[pos+1]) << 24) | (static_cast<u32>(bytes[pos+2]) << 16) | (static_cast<u32>(bytes[pos+3]) << 8) | (static_cast<u32>(bytes[pos+4]));
            f32 ret_num = *(reinterpret_cast<f32*>(&u32_num));
            obj.height = ret_num; // getting a height for return obj
            pos += 6;
            pos += bytes[pos]+1;
            if(bytes[pos] == PACK109_S8){
              pos += 1;
              string concat_name = "";
              for(int c = 1; c <= bytes[pos]; c++){ // forming a name for return obj
                concat_name += bytes[pos+c];
              }
              obj.name = concat_name;
            }else if(bytes[pos] == PACK109_S16){
              string concat_name = "";
              for(int c = 1; c <= bytes[pos]; c++){
                concat_name += bytes[pos+c];
              }
              obj.name = concat_name;
            }else{
              throw;
            }
          }
        } else {
          throw;
        }
      }else{
        throw;
      }
    }else{
      throw;
    }
  }else if(bytes[0] == PACK109_M16){ // repeat of if statement for larger map
    pos += 2;
    if(bytes[pos] == PACK109_S8){
      string ret_string = "";
      int name_len = bytes[3];
      for(int i = 0; i < name_len; i++){
        ret_string += std::to_string(bytes[i+4]);
      }
      pos += name_len+2;
      if(bytes[pos] == PACK109_M8){
        pos += 3;
        pos += bytes[pos] + 1;
        if (bytes[pos] == PACK109_U8) {
          obj.age = bytes[pos+1];
          pos += 3;
          pos += bytes[pos]+1;
          if (bytes[pos] == PACK109_F32) { 
            u32 u32_num = (static_cast<u32>(bytes[pos+1]) << 24) | (static_cast<u32>(bytes[pos+2]) << 16) | (static_cast<u32>(bytes[pos+3]) << 8) | (static_cast<u32>(bytes[pos+4]));
            f32 ret_num = *(reinterpret_cast<f32*>(&u32_num)); // forming a height for return obj
            obj.height = ret_num;
            pos += 6;
            pos += bytes[pos]+1;
            if(bytes[pos] == PACK109_S8){
              pos += 1;
              string concat_name = "";
              for(int c = 1; c <= bytes[pos]; c++){ // forming a name for return obj
                concat_name += bytes[pos+c];
              }
              obj.name = concat_name;
            }else if(bytes[pos] == PACK109_S16){
              string concat_name = "";
              for(int c = 1; c <= bytes[pos]; c++){
                concat_name += bytes[pos+c];
              }
              obj.name = concat_name;
            }else{
              throw;
            }
          }
        } else {
          throw;
        }
      }else{
        throw;
      }
    }else{
      throw;
    }
  }else{
    throw;
  }
  return obj;
}

void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}