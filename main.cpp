
#include <SFML/Graphics.hpp>
#include <iostream>
#include<unordered_map>
#include<set>
#include "Menu.h"


using namespace sf;
using namespace std;

int DijkstraVisitedNode = 0;

int IsDijkstra = 0;
static int globalState = 0;
unsigned int windowWidth = 1250;
unsigned int windowHeight = 950;
Menu menu(1250, 950, 0);

 unsigned int numBlockX{ 10 };
 unsigned int numBlockY{ 10 };

float blockWidth{ float(windowWidth) / numBlockX }; //width of each cell in the graph
float blockHeight{ float(windowHeight) / numBlockY }; //height of each cell in the grapht

float outlineThickness{ -2.f };

int horisontalAndVerticalCost{ 10 };


class Coordinate2D
{
public:
    Coordinate2D() {};
    Coordinate2D(int x, int y) : m_x(x), m_y(y) {};

    int x() const { return m_x; } //cannot be modified, called by const or any other object type
    int y() const { return m_y; }

private:
    int m_x;
    int m_y;
};

inline bool operator==(const Coordinate2D& lhs, const Coordinate2D& rhs) { // == ovoerloading
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline Coordinate2D operator+(Coordinate2D& lhs, const Coordinate2D& rhs) { //+ overloading
    return Coordinate2D(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}



struct hashFunc
{
    size_t operator()(const Coordinate2D& coordinate) const  
    {
        size_t h1 = std::hash<int>()(coordinate.x());
        size_t h2 = std::hash<int>()(coordinate.y());
        
        return h1 ^ (h2<<1);//hashing technique source:cpp refrence
    }
};

struct Node 
{
    int G = 0;//cost
    
    Coordinate2D m_coordinates;
    Node* m_parent;
    

    Node(const Coordinate2D& coordinates, Node* parent = nullptr) : m_coordinates(coordinates), m_parent(parent) {};
};

inline bool operator<(const Node& lhs, const Node& rhs) 
{
    return make_pair(lhs.m_coordinates.x(), lhs.m_coordinates.y()) < make_pair(rhs.m_coordinates.x(), rhs.m_coordinates.y()); //compares two pairszx
}

//here

struct Block
{
    RectangleShape m_shape;
    Block() {};
    Block(const Block& other) : Block(static_cast<int>(other.m_shape.getPosition().x / blockWidth),  //callinf another costructor from within
        static_cast<int>(other.m_shape.getPosition().y / blockHeight), other.m_shape.getFillColor(), other.m_shape.getOutlineColor()) {};

    Block(Color fillColor, Color outlineColor)
    {

        m_shape.setSize({ blockWidth, blockHeight });
        m_shape.setFillColor(fillColor);
        m_shape.setOutlineColor(outlineColor);
        m_shape.setOutlineThickness(outlineThickness);
    }

    Block(int x, int y, Color fillColor, Color outlineColor)
    {
        m_shape.setSize({ blockWidth, blockHeight });
        m_shape.setFillColor(fillColor);
        m_shape.setOutlineColor(outlineColor);
        m_shape.setOutlineThickness(outlineThickness);
        m_shape.setPosition(x * blockWidth, y * blockHeight);
        m_shape.setOrigin(0.f, 0.f);
    }
};

using BlockMap = unordered_map<Coordinate2D, Block, hashFunc>; //using replaces blockmap with unordered map(,,,)
using BlockPair = pair<Coordinate2D, Block>; 
BlockMap gridBlocks;
BlockMap wallBlocks;
BlockMap pathBlocks;
BlockPair sourceBlock;
BlockPair targetBlock;

set<Node*> openSet;//for non visitede nodes
set<Node*> closedSet;//for visited nodes
Node* current;//traversing node
vector<Coordinate2D> path;//for backtracking after target is found
bool running = false;
bool isTargetFound = false;

const vector<Coordinate2D> directions = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } }; //left right top bottom
sf::View calcView(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize)
{
    sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f); //2d camera view, can be manipulated to create space e,g put 0.9f instead of 1.f / back 2 values scale, front 2 values displace
    float screenwidth = windowsize.x / static_cast<float>(designedsize.x);
    float screenheight = windowsize.y / static_cast<float>(designedsize.y); //pending

    sf::View view(sf::FloatRect(1.f, 1.f, static_cast<float>(designedsize.x), static_cast<float>(designedsize.y))); //sets center of view annd shifting
    view.setViewport(viewport);

    return view;
}

void createGrid()
{
    for (int x = 0; x < numBlockX; ++x)
    {
        for (int y = 0; y < numBlockY; ++y)
        {
            //Assign each block with its property
            //And insert it in gridBlock
            Block block({ x, y, Color::White, Color{ 128, 128, 128 } }); //cell initilized, white cells
            gridBlocks.insert({ Coordinate2D(x, y), block }); //grid loaded with cells
        }
    }
}

bool traversable(const Coordinate2D coordinate)
{
    if (wallBlocks.count(coordinate) //if wall block then non traversable
        || coordinate.x() < 0
        || coordinate.x() >= numBlockX
        || coordinate.y() < 0
        || coordinate.y() >= numBlockY)
    {
        return false; 
    }

    return true; }



void explorePath()
{
    DijkstraVisitedNode++;//during traversal nodes are visited i.e node count
   
    if (!openSet.empty())
    {
        current = *openSet.begin(); //current le openset ko beginning ma point gariraxa

        
        for (Node* node : openSet) //iterator ho
        {
            if (node->G <= current->G) 
                current = node;
        }
        //Insert it in the closedSet i,e, visited node
        closedSet.insert(current);
        openSet.erase(find(openSet.begin(), openSet.end(), current));

        // Path found
        if (current->m_coordinates == targetBlock.first)
            isTargetFound = true;

        // Explore neighbours
        for (size_t i = 0; i < directions.size(); ++i)
        {
            Coordinate2D neighbourPos{ current->m_coordinates + directions[i] };
            //lambda funtion
            //neighbourPos passed as external variable
            //iterating on each element of closed set
            auto itClosed = find_if(closedSet.begin(), closedSet.end(), [&neighbourPos](const Node* node)
                {
                    return node->m_coordinates == neighbourPos;//checks if the neighbour is  in closed set
                                                               
                });
            
            if (!traversable(neighbourPos) || itClosed != closedSet.end())
                continue;
            //Goto to next neighbour

              
            int G = current->G + horisontalAndVerticalCost;
           // cout << "G:" << G<<endl;


            auto itOpen = find_if(openSet.begin(), openSet.end(), [&neighbourPos](const Node* node)
                {
                    return node->m_coordinates == neighbourPos;
                });
            //when the below condition is true new neighbour is encountered

            //here

            if (itOpen == openSet.end())
            {
                Node* neighbour = new Node(neighbourPos, current);
                neighbour->G = G;
               
               
                openSet.insert(neighbour);

            }
            //else it was already in the list to be visited , it is far form the source than the current node => current is the parent of that node
            else if (G < (*itOpen)->G)
            {
                (*itOpen)->m_parent = current;
                (*itOpen)->G = G;
            }
        }
    }

    // if target is found trace back the path to the source
    if (isTargetFound)
    {
        while (current != nullptr)
        {
            path.push_back(current->m_coordinates);
            current = current->m_parent;
        }
    }
}

void clearMemory()
{
    for (auto it = openSet.begin(); it != openSet.end();) {
        delete* it;
        it = openSet.erase(it);
    }

    for (auto it = closedSet.begin(); it != closedSet.end();) {
        delete* it;
        it = closedSet.erase(it);
    }
}

void handleInput(RenderWindow& window, const sf::Vector2u designedsize) //input ways can be modified from here
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
        {
            window.close();
            break;
        }
        case Event::KeyPressed:
        {
            if (event.key.code == Keyboard::R)
            {
                running = true;
            }
            else if (event.key.code == Keyboard::C)
            {
                clearMemory();

                wallBlocks.clear();
                pathBlocks.clear();
                sourceBlock = BlockPair();
                targetBlock = BlockPair();
                openSet.clear();
                closedSet.clear();
                current = nullptr;
                path.clear();
                running = false;
                isTargetFound = false;
                if (IsDijkstra) DijkstraVisitedNode = 0;
               
            }

            else if (event.key.code == Keyboard::Escape)
            {
                window.close();
            }
            else if (event.key.code == Keyboard::Return)
            {
                window.clear();
                globalState = 1;
            }

            else if (event.key.code == Keyboard::S || event.key.code == Keyboard::T)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                const int x = static_cast<int>(mousePos.x / blockWidth);
                const int y = static_cast<int>(mousePos.y / blockHeight);
                Coordinate2D coord(Coordinate2D(x, y));
                auto it = gridBlocks.find(coord);
                //Check if "it" is in the gridBlock and if the mouse coordinate is inside the window
                if (it != gridBlocks.end() && it->second.m_shape.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.key.code == Keyboard::S)
                    {
                        Block block({ x, y, Color{252, 36, 3}, Color::Black });
                        sourceBlock = { Coordinate2D(x, y), block };
                        openSet.clear();
                        openSet.insert(new Node(Coordinate2D(x, y)));
                    }
                    else if (event.key.code == Keyboard::T)
                    {
                        Block block({ x, y, Color{153, 255, 51}, Color::Black });
                        targetBlock = { Coordinate2D(x, y), block };
                    }
                }
            }
            break;
        }
        case Event::Resized:
        {
            window.setView(calcView(sf::Vector2u(event.size.width, event.size.height), designedsize));
            break;
        }


        default:
            break;
        }


    }
    // Toggling between the two algorithm i.e. A* (star) And Dijkstra
    if (event.key.code == Keyboard::D)
    {
        clearMemory();
        pathBlocks.clear();
        openSet.clear();
        openSet.insert(new Node(sourceBlock.first));
        closedSet.clear();
        current = nullptr;
        path.clear();
        running = false;
        isTargetFound = false;
        DijkstraVisitedNode = 0;
        IsDijkstra = 1;
    }

    if (event.key.code == Keyboard::Z)
    {
        clearMemory();
        pathBlocks.clear();
        openSet.clear();
        openSet.insert(new Node(sourceBlock.first));
        closedSet.clear();
        current = nullptr;
        path.clear();
        running = false;
        isTargetFound = false;
        
        IsDijkstra = 0;
    }

    // Creating Wall
    if (Keyboard::isKeyPressed(Keyboard::Key::W))
    {
        Vector2i mousePos = Mouse::getPosition(window);
        const int x = static_cast<int>(mousePos.x / blockWidth);
        const int y = static_cast<int>(mousePos.y / blockHeight);
        Coordinate2D coord(Coordinate2D(x, y));
        auto it = gridBlocks.find(coord);
        if (it != gridBlocks.end() && it->second.m_shape.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
        {
            Block block({ x, y, Color{183,50,57}, Color{ 128, 128, 128 } });
            wallBlocks.insert({ Coordinate2D(x, y), block });
        }

    }
    // Removing Wall
    if (Keyboard::isKeyPressed(Keyboard::Key::A))
    {
        Vector2i mousePos = Mouse::getPosition(window);
        const int x = static_cast<int>(mousePos.x / blockWidth);
        const int y = static_cast<int>(mousePos.y / blockHeight);
        Coordinate2D coord(Coordinate2D(x, y));
        auto it1 = wallBlocks.find(coord);
        if (it1 != wallBlocks.end() && it1->second.m_shape.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
        {
            Block block({ x, y, Color::White, Color{ 128, 128, 128 } });
            wallBlocks.erase(it1);
        }

    }



}
//Draw once the computation is done
void drawScene(RenderWindow& window)
{
    if (globalState == 0) {
        sf::RectangleShape rectangle;
        sf::RectangleShape insrectangle;


        rectangle.setSize(sf::Vector2f(1100, 850));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(5);
        rectangle.setOrigin(rectangle.getGlobalBounds().width / 2, rectangle.getGlobalBounds().height / 2);
        rectangle.setPosition(625, 475);
        rectangle.setFillColor(sf::Color::Black);
        window.draw(rectangle);

        insrectangle.setSize(sf::Vector2f(1100, 150));
        insrectangle.setOutlineColor(sf::Color::Red);
        insrectangle.setOutlineThickness(5);
        insrectangle.setOrigin(insrectangle.getGlobalBounds().width / 2, insrectangle.getGlobalBounds().height / 2);
        insrectangle.setPosition(625, 100);
        insrectangle.setFillColor(sf::Color::Black);

        window.draw(insrectangle);
        menu.draw(window);
    }

    else if (globalState == 1) {

        for (const auto& block : gridBlocks)
        {
            window.draw(block.second.m_shape);
        }

        for (const auto& block : wallBlocks)
        {
            window.draw(block.second.m_shape);
        }

        for (const Node* node : closedSet)
        {
            Block block({ node->m_coordinates.x(), node->m_coordinates.y(), Color{51, 153, 255}, Color::Black });
            window.draw(block.m_shape);
        }

        if (current)
        {
            Block block{ current->m_coordinates.x(), current->m_coordinates.y(), Color{46,46,184}, Color::Black };
            window.draw(block.m_shape);
        }

        for (const Coordinate2D& coordinate : path)
        {
            Block block{ coordinate.x(), coordinate.y(), Color{46,46,184}, Color::Black };
            window.draw(block.m_shape);
        }

        window.draw(sourceBlock.second.m_shape);
        window.draw(targetBlock.second.m_shape);
        sf::Font font1;
        sf::Text stats;
        string dynDijk = "Diijkstra Visited Node: " + std::to_string(DijkstraVisitedNode);
       
        if (!font1.loadFromFile("a.ttf"))
        {
            // handle error
        }
        stats.setFont(font1);
        stats.setFillColor(sf::Color::Blue);
        stats.setString(dynDijk);
        stats.setPosition(10, 910);
        window.draw(stats);

        

    }
}

int main()
{
    const sf::Vector2u designedsize(1250, 950); //gap aauxa

    RenderWindow window({ windowWidth, windowHeight }, "Path Visualiser");
    window.setView(calcView(window.getSize(), designedsize));
    window.setFramerateLimit(60);

    Clock clock;

    createGrid();

    // Window Loop
    while (window.isOpen())
    {

        window.clear();

        handleInput(window, designedsize);

        if (running && !isTargetFound)
        {
            // Delay for Visualization
            Time time = clock.getElapsedTime();
            bool timePassed = time.asMilliseconds() > 100.f;
            if (timePassed)
            {
                explorePath();
                clock.restart();
            }
        }

        drawScene(window);

        window.display();
    }

    clearMemory();


    
    cout << "Dijkstra Visited Node : " << DijkstraVisitedNode << endl;
    return 0;
}