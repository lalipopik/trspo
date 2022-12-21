#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <fstream>
#define WSIZE 800
#define WSIZEL 1800
#define PROP 0.001
#define EUQ x / (pow(x, 2) + x + 1)

using namespace std;

void timeStopper(float speed) {
    for (int i = 0; i < i + 2; i++) {
        if (i > 100000000/ speed) {
            break;
        }
    }
}

int main()
{
    //Переменные х и у
    double y;
    double x;

    //Переменные Начала отрезка и конца
    double start = 1, end = 2;
    cout << "Our equation: y = x / (pow(x, 2) + x + 1)" <<  endl;
    cout << "Lets define the boundaries (granitsy)" << endl;

    //Ввод Начала и конца
    do {
        if ((end - start < 0)) {
            cout << "error" << endl;
            cout << "Try again: " ;
        }
    cout << "Start: ";
    cin >> start;
    cout << "End:";
    cin >> end;
    } while (end - start < 0);
    
    //Определение области визначення
    double max = -10000, min = 10000;
    for (x = start; x < end; x = x + PROP) {
        y = EUQ;
        if (y > max) {
            max = y;
        }
        if (y < min) {
            min = y;
        }
    }


    //Вывод области визначення
    cout << "From " << start << " to " << end << endl;
    cout << "Defined on [" << min << "," << max << "] " << endl;
    cout << "Press Enter to draw graphic...";
    while (getchar()) {
        fflush(stdin);
        char answer; 
        answer = getchar();
        break;
    }
  
    //Определение точки
    sf::RectangleShape dot(sf::Vector2f(1, 1));
    dot.setFillColor(sf::Color::Red);

    //Определение рисунка единичной черточки
    int pipkasize = 20;
    sf::RectangleShape pipkaHor(sf::Vector2f(2, pipkasize));
    sf::RectangleShape pipkaVert(sf::Vector2f(pipkasize, 2));
    pipkaHor.setFillColor(sf::Color::White);
    pipkaVert.setFillColor(sf::Color::White);

    //Определение рисунка осей Х и У
    sf::RectangleShape rectHor(sf::Vector2f(WSIZEL, 2));
    sf::RectangleShape rectVert(sf::Vector2f(2, WSIZE));
    rectHor.setFillColor(sf::Color::White);
    rectHor.setPosition(0, WSIZE/2);
    rectVert.setFillColor(sf::Color::White);
    rectVert.setPosition(WSIZEL / 2, 0);
    
    //Загрузка шрифта для вывода текста путем мне не понятным
    std::ifstream font_file{ "20470.ttf", ifstream::binary };
    std::vector<char> buffer;
    if (font_file) {
        font_file.seekg(0, font_file.end);
        const auto length = font_file.tellg();
        if (!length) {
            std::cerr << "Cannot load zero byte texture file" << std::endl;
            return EXIT_FAILURE;
        }
        buffer.resize(length); 
        font_file.seekg(0, font_file.beg);
        auto start = &*buffer.begin();
        font_file.read(start, length);
        font_file.close();
    }
    else {
        std::cerr << "Could not open texture file" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Font font;
    if (!font.loadFromMemory(&buffer[0], buffer.size())) {
        std::cerr << "Texture load failed" << std::endl;
        return EXIT_FAILURE;
    }

    //Определение текста для значений на оси Х
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    
    //Определение текста для значений на оси У
    sf::Text textVert1;
    textVert1.setFont(font);
    textVert1.setCharacterSize(30); 
    textVert1.setFillColor(sf::Color::White);
    textVert1.setStyle(sf::Text::Bold);
    textVert1.setString("1");
    sf::Text textVert2;
    textVert2.setFont(font);
    textVert2.setCharacterSize(30); 
    textVert2.setFillColor(sf::Color::White);
    textVert2.setStyle(sf::Text::Bold);
    textVert2.setString("-1");

    //Определение окна
    sf::RenderWindow window(sf::VideoMode(WSIZEL, WSIZE), "Graph");

    //Скорость прокрутки
    float speed = 3;
    sf::Text Speed;
    Speed.setFont(font);
    Speed.setCharacterSize(30);
    Speed.setFillColor(sf::Color::White);
    Speed.setStyle(sf::Text::Bold);
    Speed.setString("Speed: ");
    Speed.setPosition(WSIZEL - 300,  80);

    sf::Text textspeed;
    textspeed.setFont(font);
    textspeed.setCharacterSize(30);
    textspeed.setFillColor(sf::Color::White);
    textspeed.setStyle(sf::Text::Bold);


    //Открытие окна
    while (window.isOpen())
    {
        //Если нажать ескэйп, то программа завершится
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        //масштабирование и хождение по графику
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            clock_t start1 = clock();
            clock_t end1 = clock();
            while ((end1 - start1) / CLOCKS_PER_SEC < 0.1) {
                end1 = clock();
            }
            start--;
            end--;
            cout << start << " " << end << endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            clock_t start1 = clock();
            clock_t end1 = clock();
            while ((end1 - start1) / CLOCKS_PER_SEC < 0.1) {
                end1 = clock();
            }
            start++;
            end++;
            cout << start << " " << end << endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            clock_t start1 = clock();
            clock_t end1 = clock();
            while ((end1 - start1) / CLOCKS_PER_SEC < 0.1) {
                end1 = clock();
            }
            start--;
            end++;
            cout << start << " " << end << endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            clock_t start1 = clock();
            clock_t end1 = clock();
            while ((end1 - start1) / CLOCKS_PER_SEC < 0.1) {
                end1 = clock();
            }
            start++;
            end--;
            cout << start << " " << end << endl;
        }
        */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            speed = speed - 0.1;
        }    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            speed = speed + 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            //window.close();
            timeStopper(speed);
            start--;
            end--;
            //sf::RenderWindow window(sf::VideoMode(WSIZEL, WSIZE), "Graph");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            //window.close();
            timeStopper(speed);
            start++;
            end++;
            //sf::RenderWindow window(sf::VideoMode(WSIZEL, WSIZE), "Graph");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            timeStopper(speed);
            start--;
            end++;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            timeStopper(speed);
            start++;
            end--;

        }
        while (start >= end) {
            start--;
            end++;
        }
        if (speed < 0.1) {
            speed = speed + 0.1;
        }
        if (speed > 10) {
            speed = speed - 0.1;
        }

        window.clear();

        //Отрисовка скорости
        window.draw(Speed);
        textspeed.setPosition(WSIZEL - 200, 80);
        int first = speed * 10 / 10;
        switch (first)
        {
        case 0:
            textspeed.setString("0");
            break;
        case 1:
            textspeed.setString("1");
            break;
        case 2:
            textspeed.setString("2");
            break;
        case 3:
            textspeed.setString("3");
            break;
        case 4:
            textspeed.setString("4");
            break;
        case 5:
            textspeed.setString("5");
            break;
        case 6:
            textspeed.setString("6");
            break;
        case 7:
            textspeed.setString("7");
            break;
        case 8:
            textspeed.setString("8");
            break;
        case 9:
            textspeed.setString("9");
            break;
        }
        window.draw(textspeed);
        int second = (int)(speed * 10) % 10;
        switch (second)
        {
        case 0:
            textspeed.setString("0");
            break;
        case 1:
            textspeed.setString("1");
            break;
        case 2:
            textspeed.setString("2");
            break;
        case 3:
            textspeed.setString("3");
            break;
        case 4:
            textspeed.setString("4");
            break;
        case 5:
            textspeed.setString("5");
            break;
        case 6:
            textspeed.setString("6");
            break;
        case 7:
            textspeed.setString("7");
            break;
        case 8:
            textspeed.setString("8");
            break;
        case 9:
            textspeed.setString("9");
            break;
        }
        textspeed.setPosition(WSIZEL - 180, 80);
        window.draw(textspeed);




        //Вспомогательные переменные
        float iterations = (end - start) / PROP;  //Количество точек на графике
        long double WindSec = (WSIZEL - 100) / (end - start); //Смещение следующего единичного отрезка в пикселях
        long double Xindex = (WSIZEL - 100) / iterations; //Положение точки на оси Х

        //Вывод значений на оси Х
        int text_start = 40;
        int tempX = start;
        for (int i = text_start; i < WSIZEL; i = i + WindSec)
        {
        int tempSec = text_start;
        string str = to_string(tempX);
        tempX++;
        char t[10];
        strcpy_s(t, str.c_str());
        text.setPosition(text_start, WSIZE / 2 - pipkasize / 2 + 25);
        int g = 0;
        while (t[g] != '\0') {
            switch (t[g])
            {
            case '-':
                text.setString("-");
                break;
            case '0' :
                text.setString("0");
                break;
            case '1':
                text.setString("1");
                break;
            case '2':
                text.setString("2");
                break;
            case '3':
                text.setString("3");
                break;
            case '4':
                text.setString("4");
                break;
            case '5':
                text.setString("5");
                break;
            case '6':
                text.setString("6");
                break;
            case '7':
                text.setString("7");
                break;
            case '8':
                text.setString("8");
                break;
            case '9':
                text.setString("9");
                break;
            }
            g++;
            text.setPosition(tempSec, WSIZE / 2 - pipkasize / 2 + 25);
            tempSec = tempSec + 10;
            window.draw(text);
        }
        text_start = text_start + WindSec;
        }


        //Опредение положения оси У и рисовка единичных отрезков оси У
        int Suk = 50;
        if (start >= 0) {
            pipkaVert.setPosition(25 - pipkasize / 2, Suk);
            textVert1.setPosition(25 - pipkasize / 2 + 30, Suk - 20);
            window.draw(textVert1);
            window.draw(pipkaVert);
            pipkaVert.setPosition(25 - pipkasize / 2, WSIZE - 50);
            textVert2.setPosition(25 - pipkasize / 2 + 30, WSIZE - 50 - 20);
            window.draw(textVert2);
            window.draw(pipkaVert);
            rectVert.setPosition(25, 0);
        }
        if (end <= 0) {
            pipkaVert.setPosition(WSIZEL - 25 - pipkasize / 2, Suk);
            textVert1.setPosition(WSIZEL - 25 - pipkasize -20, Suk - 20);
            window.draw(textVert1);
            window.draw(pipkaVert);
            pipkaVert.setPosition(WSIZEL - 25 - pipkasize / 2, WSIZE - 50);
            textVert2.setPosition(WSIZEL - 25 - pipkasize - 20, WSIZE - 50 - 20);
            window.draw(textVert2);
            window.draw(pipkaVert);
            rectVert.setPosition(WSIZEL - 25, 0);
        }
        if (end >= 0 && start <= 0) {
            int count = 0;
            for (x = start; x < end; x = x ++) {
                if (x == 0) {
                    rectVert.setPosition(50 + count*WindSec, 0);
                break;
                }
                count++;
            }
            pipkaVert.setPosition(50 + count * WindSec - pipkasize / 2, Suk);
            textVert1.setPosition(50 + count * WindSec - pipkasize - 20, Suk - 20);
            window.draw(textVert1);
            window.draw(pipkaVert);
            pipkaVert.setPosition(50 + count * WindSec - pipkasize / 2, WSIZE - 50);
            textVert2.setPosition(50 + count * WindSec - pipkasize - 20, WSIZE - 50 - 20);
            window.draw(textVert2);
            window.draw(pipkaVert);
        }

        //Рисовка единичных отрезков на оси Х
        Suk = 50;
        long double suk2 = Suk;
        pipkaHor.setPosition(Suk, WSIZE / 2 - pipkasize/2);
        window.draw(pipkaHor);
        for (int i = suk2; i < WSIZEL; i = i + (WindSec)) {
            suk2 = suk2 + (WindSec);
            pipkaHor.setPosition(suk2, WSIZE / 2 - pipkasize / 2);
            window.draw(pipkaHor);
        }
        
        //Рисовка осей Х и У
        window.draw(rectHor);
        window.draw(rectVert);

        //Рисовка графика
        long double FirstXpos = 50;
        float Yindex;
        int Position = 50;
        for (x = start; x < end; x = x + PROP) {
            y = EUQ;
            Yindex = ((WSIZE - 100) * (y + 1) / 2) + 50;
            Yindex = WSIZE  - Yindex;
            /*
                if (sf::IntRect(Position - 10, Yindex-10, 20, 20).contains(sf::Mouse::getPosition(window))) {
                    sf::Text tetxy;
                    tetxy.setFont(font);
                    tetxy.setCharacterSize(30);
                    tetxy.setFillColor(sf::Color::White);
                    tetxy.setStyle(sf::Text::Bold);
                    tetxy.setString("y: ");
                    tetxy.setPosition(Position, Yindex - 40);
                    sf::Text tetxx;
                    tetxx.setFont(font);
                    tetxx.setCharacterSize(30);
                    tetxx.setFillColor(sf::Color::White);
                    tetxx.setStyle(sf::Text::Bold);
                    tetxx.setString("x: ");
                    tetxx.setPosition(Position + 50, Yindex - 40);

                    window.draw(tetxy);
                    window.draw(tetxx);
                }
            
            */
            dot.setPosition(  FirstXpos,Yindex );
            FirstXpos = FirstXpos + Xindex;
            window.draw(dot);
        }

        //Вывод
        window.display();
    }
    return 0;
}