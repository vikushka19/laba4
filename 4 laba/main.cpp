#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class MyText {
private:
    string text;
    float showTime; //в секундах
    sf::Font font;//шрифт
    sf::Text displayText;
    sf::SoundBuffer buffer;/*используется для загрузки звуковых данных
    из файла или для хранения звуковых данных в памяти.*/
    sf::Sound soundEffect;//звук

public:
    MyText(const string& inputText, float time) : text(inputText), showTime(time) {
        font.loadFromFile("arial.ttf");//откуда берем шрифт
        displayText.setFont(font);//установка шрифта
        displayText.setCharacterSize(50);//начальный размер шрифта в пикселях
        displayText.setFillColor(sf::Color::Red);
        displayText.setString("");
        buffer.loadFromFile("zvuk.wav");//звук
        soundEffect.setBuffer(buffer);//установка звука для сигнала
    }
    void verbAnimationText(sf::RenderWindow& window) {
        srand(time(NULL));
        int startsize = displayText.getCharacterSize();
        int oldsize = startsize;
        cout << "start: " << startsize << endl;
        int speed = showTime / text.size();
        for (size_t i = 0; i < text.size(); i++) {
            //рандомное изменение размера шрифта в диапазоне от -10 до 10 пунктов
            int changesize = (rand() % 21) - 10;
            int newsize = oldsize + changesize;
            //проверка диапазона
            while (changesize == 0 || newsize < startsize - 10 || newsize > startsize + 10) {
                changesize = (rand() % 21) - 10;
                newsize = oldsize + changesize;
            }
            cout <<"change: "<< changesize << endl;
            cout <<"new: " << newsize << endl;
            displayText.setString(displayText.getString() + text[i]);
            displayText.setCharacterSize(newsize);
            
            window.clear();
            window.draw(displayText);
            window.display();
            oldsize = newsize;
            sf::sleep(sf::seconds(speed));
        }

        soundEffect.play();
        
        cout<<"time to show:"<< showTime;
       
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Text motion");

    MyText animatedText("Hello, world! 448", 5);
    animatedText.verbAnimationText(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    return 0;
}

//ЧТО НАДО ДОБАВИТЬ/ИСПРАВИТЬ:
//в консоль вывести фактическое время вывода строки,а не просто значение showTime
//сделать так,чтобы строка выводилась столько времени,сколько в showTime,но с одинаковой скоростью (какой интервал между символами???)
