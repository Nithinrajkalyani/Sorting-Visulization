#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <random>
#include<iostream>
#include<ctime>

void swap_(int arr[], int, int);
void bubble_sort(int bars[], int size);
void drawBars(sf::RenderWindow& window, int heights[]);
void quick_sort(int bars[], int first, int last);
void shuffleArray(int bars[]);
void merge_sort(int bars[], int start, int end);
void merge_arrays(int bars[], int start, int mid, int end);
void heap_sort(int bars[], int size);
void percolate_down(int bars[], int index, int size);

static const int WINDOW_HEIGHT = 600;           
static const int WINDOW_WIDTH = 1000;
static const float bar_width = 3.0f;
static const int bars_count = WINDOW_WIDTH / bar_width; 

bool quit = false;


sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Visualizer");  //It defines an OS window that can be painted using the other classes of the graphics module

//Creating Rectangle Bars 
void drawBars(sf::RenderWindow& window, int heights[])
{
    window.clear();
    for (int x = 0; x < bars_count; x++)
    {
        //Fade colour for Bars when Program has been startet
        int height = heights[x];
        int colorValue = (int)(255.0f * (height / (float)WINDOW_HEIGHT));
        sf::Color color(colorValue, 255 - colorValue, 0);


        // Creating Rectangle Shape of Bar  sf::Vector2f Is used to manipulating 2-dimensional vectors it will take X as bar_width and Y as height of Rectangle Bar
          
        sf::RectangleShape bar(sf::Vector2f(bar_width, height));    

        bar.setFillColor(color);
        bar.setPosition(sf::Vector2f(bar_width * x, WINDOW_HEIGHT - bar.getSize().y));   // set postion of Random Rectangle Bar in window 

        window.draw(bar); // Draw Rectangle Bar on window
    }

    window.display();    // Display on the screen what we have Done
    
}

// Change Bar Colour of Each sorting algorithm 
void changeBarColor(int index, sf::Color color, int bars[]) 
{
    sf::RectangleShape bar(sf::Vector2f(bar_width, bars[index]));
    bar.setFillColor(color);
    bar.setPosition(sf::Vector2f(bar_width * index, WINDOW_HEIGHT - bar.getSize().y));          
    window.draw(bar);               // It is used that after sorting we are drawing the change colour 
    window.display();
}

//Creating Fade colour Take paramete as height and sortType as which sorting algorithm
sf::Color getColor(int height, int sortType) 
{
    // In SFML it has having RGB colour So we have taken 3 variables as RGB and performed operation on that used 255 Because It is Highest rgb colour
    float max_height = float(WINDOW_HEIGHT);
    float shift = float(255 / max_height);
    float increase = shift * (height);
    float decrease = 255 - increase;
 
    /*   
     As SortType
    
        QuickSort : 1
        Bubble sort : 2
        Merge sort : 3 
        Heap sort : 4
        insertion sort : 5
        selection_sort : 6
    */
     
    switch (sortType) {
    case 0:
        // Blue -> Purple
        return sf::Color(increase, decrease, 255);

    case 1:
        // Red -> Yellow
        return sf::Color(255, increase, 0);

    case 2:
        // Red -> Purple
        return sf::Color(255, 0, increase);

    case 3:
        // Green -> Yellow
        return sf::Color(increase, 255, 0);

    case 4:
        // Purple -> Yellow
        return sf::Color(255, decrease, increase);

    case 5:
        // Cyan -> Red
        return sf::Color(increase, decrease, decrease);
    case 6:
        // cyan - > yellow
        return sf::Color(increase, increase, decrease);

    default:
        // Red if it fails
        return sf::Color::Red;
    }
}

void shuffleArray(int bars[])
{
    std::cout << "Shuffling " << std::endl;
    std::cout << "Started Shuffling " << std::endl;
    for (int k = bars_count - 1; k >= 1; k--)
    {
        int random = rand() % k;
        swap_(bars, random, k);
    }

}

void swap_(int bars[], int index1, int index2)
{

    std::swap(bars[index1], bars[index2]);
    drawBars(window, bars);
}

void percolate_down(int bars[], int index, int size)
{
    int child;
    int temp = bars[index];

    for (; 2 * index < size - 1; index = child)
    {
        child = 2 * index + 1;
        if (child != size - 1 && bars[child] < bars[child + 1])

        {

            child++;
        }
        if (bars[child] > temp)
        {
            bars[index] = bars[child];
        }
        else break; // largest is parent, done

    }
    bars[index] = temp;
}

void heap_sort(int bars[], int size)
{
    //heapify the bars
    std::cout << "Building heap..." << std::endl;

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        percolate_down(bars, i, size);
        drawBars(window, bars);
    }
    std::cout << "Sorting" << std::endl;
    for (int j = size - 1; j > 0; j--)
    {
        swap_(bars, 0, j);
        percolate_down(bars, 0, j);
    }
}

void heap_colour(int bars[], int size)
{
    for (int i = 0; i < bars_count; i++) {
        changeBarColor(i, getColor(bars[i], 4), bars);
    }
}

void merge_arrays(int bars[], int start, int mid, int end)
{
    int index = start;
    int start1 = start;
    int start2 = mid + 1;
    int last1 = mid;
    int last2 = end;
    int *temp = new int[bars_count];

    for (; (start1 <= last1) && (start2 <= last2); index++)
    {
        if (bars[start1] <= bars[start2])
        {
            temp[index] = bars[start1];
            start1++;
        }
        else
        {
            temp[index] = bars[start2];
            start2++;
        }
    }

    for (; start2 <= last2; start2++, index++)
    {
        temp[index] = bars[start2];
    }
    for (; start1 <= last1; start1++, index++)
    {
        temp[index] = bars[start1];
    }
    for (index = start; index <= end; index++)
    {
        bars[index] = temp[index];
        drawBars(window, bars);
    }
    delete[] temp;
}

void merge_sort(int bars[], int start, int end)
{
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    
        merge_sort(bars, start, mid);
        merge_sort(bars, mid + 1, end);
        merge_arrays(bars, start, mid, end);
    
}

void merge_colour(int bars[], int start, int end) 
{
    for (int i = 0; i < bars_count; i++) 
    {
        changeBarColor(i, getColor(bars[i], 3), bars);
    }
}

void bubble_sort(int bars[], int size) {
    bool swapped = true;
    sf::Clock clock;
    while (swapped) {
        swapped = false;
        for (int i = 1; i < size; i++) 
        {
            if (bars[i - 1] > bars[i]) 
            {
                swap_(bars, i, i - 1);
                swapped = true;
            }
        }
        size--;
    }
    
}

void bubble_colour(int bars[], int size)
{
    for (int i = 0; i < bars_count; i++) {
        changeBarColor(i, getColor(bars[i], 0), bars);
    }
}

int partition(int bars[], int first, int last)
{

    int pivot = bars[(int)std::floor((first + last) / 2)];
    int i = first - 1;
    int j = last + 1;
    while (true)
    {
        do
        {
            i++;
        } while (bars[i] < pivot);
        do
        {
            j--;
        } while (bars[j] > pivot);
        if (i >= j)
            return j;
        swap_(bars, i, j);
    }
}

void quick_sort(int bars[], int first, int last)
{
    if (first < last)
    {
        int pivot = partition(bars, first, last);
        quick_sort(bars, first, pivot);
        quick_sort(bars, pivot + 1, last);
        
    }

}

void quick_colour(int bars[], int first, int last)
{
    for (int i = 0; i < bars_count; i++) {
        changeBarColor(i, getColor(bars[i], 1), bars);
    }
}

void insertion_sort(int bars[], int size) {
    int key, j;
    for (int i = 1; i < size; i++) {
        key = bars[i];
        j = i - 1;

        while (j >= 0 && bars[j] > key) {
            bars[j + 1] = bars[j];
            j = j - 1;
            
        }
        bars[j + 1] = key;
        drawBars(window, bars);
    }
}

void insertion_colour(int bars[], int size)
{
    for (int i = 0; i < bars_count; i++) {
        changeBarColor(i, getColor(bars[i], 5), bars);
    }
}

void selection_sort(int bars[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (bars[j] < bars[min_index]) {
                min_index = j;
            }
        }
        swap_(bars, i, min_index);
    }
}

void selection_colour(int bars[], int size)
{
    for (int i = 0; i < bars_count; i++) {
        changeBarColor(i, getColor(bars[i], 6), bars);
    }
}

void generateNewBars(int bars[])
{

    for (int i = 0; i < bars_count; i++) 
    {
        bars[i] = rand() % (WINDOW_HEIGHT - 50);
    }
    drawBars(window, bars);
}

void quitfunction()
{
    quit = true;
}






int main()
{
    // ===== CONSTRUCTUING BARS ==== //

   // srand(time(NULL));
    bool isSorted = false;
    int* heights = new int[bars_count];

    for (int i = 0; i < bars_count; i++)
    {
        heights[i] = rand() % (WINDOW_HEIGHT-50);
    }

    drawBars(window, heights);

    std::cout << "sorting Visulizer" << std::endl;
    std::cout << "    QuickSort : 1"<< std::endl;
    std::cout << "    Bubble sort : 2" << std::endl;
    std::cout << "    Merge sort : 3" << std::endl;
    std::cout << "    Heap sort : 4" << std::endl;
    std::cout << "    insertion sort : 5" << std::endl;
    std::cout << "    selection_sort : 6" << std::endl;
    std::cout << "    shuffle : 7" << std::endl;
    std::cout << "    New : 8" << std::endl;
    std::cout << "    quit : 9" << std::endl;

    while (window.isOpen() && !quit)
    {
        sf::Event event;
       
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            if (isSorted)
                shuffleArray(heights);

            std::cout << "Started Quick sort" << std::endl;

            quick_sort(heights, 0, bars_count - 1);
            quick_colour(heights, 0, bars_count - 1);

            std::cout << "Completed Quick sort" << std::endl;
                isSorted = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            if (isSorted) 
                shuffleArray(heights);

            std::cout << "Started Bubble sort" << std::endl;

            bubble_sort(heights, bars_count);
            bubble_colour(heights, bars_count);

            std::cout << "Completed Bubble sort" << std::endl;
                isSorted = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            if (isSorted)
                shuffleArray(heights);

            std::cout << "Started Merge sort" << std::endl;

            merge_sort(heights, 0, bars_count - 1);
            merge_colour(heights, 0, bars_count - 1);                  

            std::cout << "Completed Merge sort" << std::endl;
                isSorted = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            if (isSorted) 
                shuffleArray(heights);

            std::cout << "Started Heap sort" << std::endl;

            heap_sort(heights, bars_count);
            heap_colour(heights, bars_count);

            std::cout << "Completed Heap sort" << std::endl;
                isSorted = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            if (isSorted) 
                shuffleArray(heights);

            std::cout << "Started Insertion sort" << std::endl;

            insertion_sort(heights, bars_count);
            insertion_colour(heights, bars_count);

            std::cout << "Completed Insertion sort" << std::endl;
                isSorted = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        {
            if (isSorted) 
                shuffleArray(heights);

            std::cout << "Started Selection sort" << std::endl;

            selection_sort(heights, bars_count);
            selection_colour(heights, bars_count);

            std::cout << "Completed Selection sort" << std::endl;
                isSorted = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        {
            shuffleArray(heights);

            std::cout << "Shuffle" << std::endl;
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        {
            generateNewBars(heights);

            Sleep(500);
            std::cout << "New Blocks" << std::endl;
     
        }
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            {
                quitfunction();
                std::cout << "quit" << std::endl;
            }
        }
        //drawBars(window, heights);
    }
   

    delete[] heights;

    return 0;
}
