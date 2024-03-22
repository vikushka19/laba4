#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
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
        //cout << "start: " << startsize << endl;
        //ЗАПУСК СЕКУНДОМЕРА!
        sf::Clock clock;
        float speed = showTime / text.size();//интервал между символами

        for (size_t i = 0; i < text.size(); i++) {

            //рандомное изменение размера шрифта в диапазоне от -10 до 10 пунктов
            int changesize = (rand() % 21) - 10;
            int newsize = oldsize + changesize;

            //проверка диапазона
            while (changesize == 0 || newsize < startsize - 10 || newsize > startsize + 10) {
                changesize = (rand() % 21) - 10;
                newsize = oldsize + changesize;
            }
            //cout <<"change: "<< changesize << endl;
            //cout <<"new: " << newsize << endl;

            displayText.setString(displayText.getString() + text[i]);
            displayText.setCharacterSize(newsize);

            window.clear();
            window.draw(displayText);
            window.display();
            oldsize = newsize;

            //играю со временем
            sf::Time musttime = sf::seconds(speed * (i + 1));//должно пройти времени с учетом времени/символ
            sf::Time elapsed = clock.getElapsedTime();//фактически прошло времени
            if (elapsed < musttime) {//если прошло мало времени,то спим,чтобы нагнать время и дальше печатать
                sf::sleep(musttime - elapsed);
            }
        }
        soundEffect.play();
        sf::Time vsegotime = clock.getElapsedTime();//прошло времени с момента начала вывода
        cout << "fact show time: " << vsegotime.asSeconds() << " s" << endl;
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Text motion");

    MyText animatedText("Hi world people", 10);
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
