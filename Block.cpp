#include <sstream>
#include "Block.h"
#include "sha256.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
  _nNonce = -1;
  _tTime = time(nullptr);
}

string Block::GetHash()
{
  return _sHash;
}

void Block::MineBlock(uint32_t nDifficulty)
{
  char cstr[nDifficulty + 1];
  for (uint32_t i = 0; i < nDifficulty; ++i)
  {
    cstr[i] = '0';
  }
  cstr[nDifficulty] = '\0';

  string str(cstr);

  do
  {
    _nNonce++;
    _sHash = _CalculateHash();
  } while (_sHash.substr(0, nDifficulty) != str);

  cout << "Block mined: " << _sHash << " Nonce: " << _nNonce << endl;
}

inline string Block::_CalculateHash() const
{
  stringstream ss;
  ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;
  ss << _nIndex << " " << _tTime << " " << _sData << " " << _nNonce << " " << sPrevHash;
  // cout << ss.str() << endl;
  return sha256(ss.str());
}
