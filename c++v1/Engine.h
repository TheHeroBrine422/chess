#ifndef C__V1_ENGINE_H
#define C__V1_ENGINE_H

#include "senjo/ChessEngine.h"

using namespace std;

class Engine : public senjo::ChessEngine {
public:
    //--------------------------------------------------------------------------
    // senjo::ChessEngine methods (implemented in Clubfoot.cpp)
    //--------------------------------------------------------------------------
    string GetEngineName() const;
    string GetEngineVersion() const;
    string GetAuthorName() const;
    string GetCountryName() const;
    string GetFEN() const;
    list<senjo::EngineOption> GetOptions() const;
    bool SetEngineOption(const std::string& name, const std::string& value);
    bool IsInitialized() const;
    bool WhiteToMove() const;
    const char* SetPosition(const char* fen);
    const char* MakeMove(const char* str);
    void PrintBoard() const;
    void Initialize();
    void ClearSearchData();
    void PonderHit();
    void Quit();
    void ResetStatsTotals();
    void ShowStatsTotals() const;
    void GetStats(int* depth,
                  int* seldepth = NULL,
                  uint64_t* nodes = NULL,
                  uint64_t* qnodes = NULL,
                  uint64_t* msecs = NULL,
                  int* movenum = NULL,
                  char* move = NULL,
                  const size_t movelen = 0) const;

protected:
    //--------------------------------------------------------------------------
    // senjo::ChessEngine methods (implemented in ClubFoot.cpp)
    //--------------------------------------------------------------------------
    uint64_t MyPerft(const int depth);
    std::string MyGo(const int depth,
                     const int movestogo = 0,
                     const uint64_t movetime = 0,
                     const uint64_t wtime = 0, const uint64_t winc = 0,
                     const uint64_t btime = 0, const uint64_t binc = 0,
                     std::string* ponder = NULL);


    // implement required ChessEngine methods
    // see ChessEngine.h for documentation
};

#endif //C__V1_ENGINE_H
