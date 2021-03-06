#pragma once


//プロトタイプ宣言
bool UnitVec(float*vx, float*vy);

float GetAtan2Angle(float w, float h); //高さと幅で角を求める

void MapChanger(int m,int m_map[MAP_X][MAP_Y], unique_ptr<wchar_t>* p);

float SpawnChangerX(int m);

float SpawnChangerY(int m);


void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p);

void HitBoxChanger(int m, int m_map[MAP_X][MAP_Y],bool room_in,int r,int r_map[ROOM_X][ROOM_Y]);

void EnemySpawnChanger(int m, int m_map[MAP_X][MAP_Y], bool room_in);

