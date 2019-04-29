#include "stdafx.h"
#include "PathFinder.h"
#include "SimpleTileMap.h"


// Pathfinder class written during school.

Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
    delete[] m_Nodes;
    delete[] m_OpenNodes;
}

Pathfinder::Pathfinder(CSimpleTileMap* pTilemap, int width, int height)
{
    m_pTilemap = pTilemap;

    m_NumNodes = 16 * 16;

    m_Nodes = new PathNode[m_NumNodes];
    m_OpenNodes = new int[m_NumNodes];

    m_MapWidth = width;
    m_MapHeight = height;

    Reset();
}



void Pathfinder::Reset()
{
    m_NumOpen = 0;

    for (int i = 0; i<m_NumNodes; i++)
    {
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].status = PathNode::Unchecked;

        m_Nodes[i].f = 0;
        m_Nodes[i].g = FLT_MAX; // set g to be highest cost possible, so any comparison will be better.
        m_Nodes[i].h = -1; // -1 indicates the heuristic hasn't been calculated yet.
    }
}

bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    Reset();

    int StartingIndex = CalculateNodeIndex(sx, sy); // Calculate the Starting index using a start x and y
    int EndingIndex = CalculateNodeIndex(ex, ey); // Calculate the Ending index using an end x and y

                                                  // set starting node cost to zero, then add it to the open list to start the process.

    m_Nodes[StartingIndex].g = 0;
    AddToOpen(StartingIndex); // Add it


    while (true)
    {
        // find the lowest F and remove it from the open list.
        int NodeLowestF = FindNodeWithLowestFInOpen();
        RemoveFromOpen(NodeLowestF);


        // if we found the end node, we're done.
        if (NodeLowestF == EndingIndex)
        {
            return true;
        }

        // mark it as closed
        m_Nodes[NodeLowestF].status = PathNode::Closed;





        // add neighbours to open list
        AddNeighboursToOpenList(NodeLowestF, EndingIndex);



        // if we're out of nodes to check, then we're done without finding the end node.
        if (m_NumOpen == 0)
            return false;
    }


    return false;
}

int Pathfinder::GetPath(int* path, int maxdistance, int ex, int ey)
{
    int nodeIndex = CalculateNodeIndex(ex, ey);

    int length = 0;
    while (true)
    {
        if (path != nullptr && length >= maxdistance)
            return -1; // path didn't fit in size.

        if (path != nullptr) // if no path array is passed in, just get the length
            path[length] = nodeIndex;
        length++;

        nodeIndex = m_Nodes[nodeIndex].parentNodeIndex;

        if (nodeIndex == -1)
            return length;
    }


    return -1;
}

void Pathfinder::AddToOpen(int nodeindex)
{
  

    // if the node isn't already open, then add it to the list.
    if (m_Nodes[nodeindex].status != PathNode::Open)
    {
        m_OpenNodes[m_NumOpen] = nodeindex;
        m_NumOpen++;
        m_Nodes[nodeindex].status = PathNode::Open;
    }
}

void Pathfinder::RemoveFromOpen(int nodeindex)
{
    // remove the node from the open list, since we don't care about order, replace the node we're removing with the last node in list
    for (int i = 0; i<m_NumOpen; i++)
    {
        if (m_OpenNodes[i] == nodeindex)
        {
            m_NumOpen--;
            m_OpenNodes[i] = m_OpenNodes[m_NumOpen];
            return;
        }
    }
}

int Pathfinder::FindNodeWithLowestFInOpen()
{
    // loop through the nodes in the open list, then find and return the node with the lowest f score
    float LowestF = FLT_MAX; // Maximum node index, that way the first node checked will always be the lowest
    int Index = 0;

    for (int i = 0; i < m_NumOpen; i++) // Loop through the open nodes based on the amount that are open
    {
        if (m_Nodes[m_OpenNodes[i]].f < LowestF) // Check to see if the available nodes in the open list are open
        {
            LowestF = m_Nodes[m_OpenNodes[i]].f; // Set the previously Lowest F to the new one.
            Index = m_OpenNodes[i]; // Get the index of the lowest F
        }

    }

    return Index;
}

int Pathfinder::CalculateNodeIndex(int tx, int ty)
{


    // calculate the node index based on the tiles x/y

    int Index = ty * m_MapWidth + tx; // calculates a tile index
    return Index;
}

int Pathfinder::CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty)
{
    // if the node is out of bounds, return -1 (an invalid tile index)

    if (tx < 0 || tx >= 10 || ty < 0 || ty >= 10) // Values that define the size of the map
    {
        return -1;
    }

    // if the node is already closed, return -1 (an invalid tile index)

    if (m_Nodes[CalculateNodeIndex(tx, ty)].status == PathNode::Closed)
    {
        return -1;
    }

    // if the node can't be walked on, return -1 (an invalid tile index)

    if (m_pTilemap->GetTileMapValue(tx, ty) != EMapValue::FLOOR)
    {
        return -1;
    }

    // return a valid tile index
    return CalculateNodeIndex(tx, ty);
}

void Pathfinder::AddNeighboursToOpenList(int nodeIndex, int endNodeIndex)
{
    // calculate the tile x/y based on the nodeIndex

    int NodeX = nodeIndex % m_MapWidth;
    int NodeY = nodeIndex / m_MapHeight;

    // create an array of the four neighbour tiles
    Vector2Int NeighbouringTiles[4] = {
        Vector2Int(NodeX , NodeY + 1), // Top neighbour
        Vector2Int(NodeX ,  NodeY - 1), // Bottom neighbour
        Vector2Int(NodeX - 1 , NodeY), // Left neighbour
        Vector2Int(NodeX + 1, NodeY) // Right neighbour
    };


    // loop through the array
    for (int i = 0; i<4; i++)
    {
        // check if the node to add has a valid node index
        int ValidNodeIndex = CheckIfNodeIsClearAndReturnNodeIndex(NeighbouringTiles[i].x, NeighbouringTiles[i].y);
        if (ValidNodeIndex != -1)
        {
            // add the node to the open list
            AddToOpen(ValidNodeIndex);

            // if the cost to get there from here is less than the previous cost to get there, then overwrite the values.
            if (m_Nodes[nodeIndex].g + 1 < m_Nodes[ValidNodeIndex].g)
            {
                // set the parent node.
                m_Nodes[ValidNodeIndex].parentNodeIndex = nodeIndex;


                // calculate the cost to travel to that node.
                m_Nodes[ValidNodeIndex].g = m_Nodes[nodeIndex].g + 1;





                // if we haven't already calculated the heuristic, calculate it.
                // Check to see if its -1, meaning 
                if (m_Nodes[ValidNodeIndex].h == -1)

                {
                    m_Nodes[ValidNodeIndex].h = CalculateH(ValidNodeIndex, endNodeIndex);
                }


                // calculate the final value
                m_Nodes[ValidNodeIndex].f = m_Nodes[ValidNodeIndex].g + m_Nodes[ValidNodeIndex].h;
            }
        }
    }
}

float Pathfinder::CalculateH(int nodeIndex1, int nodeIndex2)
{

    int Node1x = nodeIndex1 % 10; // Tile X index
    int Node1y = nodeIndex1 / 10; // Tile Y index

    int Node2x = nodeIndex2 % 10; // Tile X index
    int Node2y = nodeIndex2 / 10; // Tile Y index

                                  // calculate the h score using the manhatten distance (absolute diff in x + absolute diff in y)
    int Manhattan = (abs(Node2x - Node1x) + abs(Node2y - Node1y));


    float hScore = (float)Manhattan;
    return hScore;

}