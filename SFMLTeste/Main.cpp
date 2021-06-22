#include <SFML/Graphics.hpp>
#include <string> 

float LarguraTela = 400;
float AlturaTela = 240;

int PontosPlayer = 0;
int PontosPlayer2 = 0;

sf::RenderWindow window(sf::VideoMode(LarguraTela, AlturaTela), "Pong");

void DesenharTexto(std::string texto, float X, float Y, float Size, sf::Color cor) {
    sf::Font font;
    if (!font.loadFromFile("8-bit fortress.ttf")) {
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(texto);
    text.setCharacterSize(Size);
    text.setFillColor(cor);
    text.setPosition(X, Y);
    window.draw(text);
}

void DesenharRetangulo(float x, float y, float width, float height, sf::Color Cor) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(Cor);
    rectangle.setPosition(x, y);
    window.draw(rectangle);
}

sf::Color White = sf::Color(250, 250, 250);
sf::Color Grey = sf::Color(156, 156, 156);

class Player {
    public:
        float X = LarguraTela - 16;
        float Y = AlturaTela / 2 - 20;
        float Largura = 8;
        float Altura = 40;
        float Velocidade = 10;
        sf::Color Cor = White;
};

class Player2 {
public:
    float X = 0 + 8;
    float Y = AlturaTela / 2 - 20;
    float Largura = 8;
    float Altura = 40;
    float Velocidade = 10;
    sf::Color Cor = White;
};

class Bola {
public:
    float X = LarguraTela / 2;
    float Y = AlturaTela / 2 - 4;
    float Largura = 8;
    float Altura = 8;
    float Velocidade = 1;
    int DirecaoX = 1;
    int DirecaoY = 1;
    sf::Color Cor = White;
};

Player player;
Player2 player2;
Bola bola;
Bola Novabola;

bool Pause = false;

void DesenharPlayer() {
    DesenharRetangulo(player.X, player.Y, player.Largura, player.Altura, player.Cor);
}

void DesenharPlayer2() {
    DesenharRetangulo(player2.X, player2.Y, player2.Largura, player2.Altura, player2.Cor);
}

void DesenharBola() {

    DesenharRetangulo(bola.X, bola.Y, bola.Largura, bola.Altura, bola.Cor);
}

void InputPlayer1() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        
        player.Y = player.Y - player.Velocidade;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player.Y = player.Y + player.Velocidade;
    }

    if (player.Y < 0) {
        player.Y = 0;
    }
    else if (player.Y  > AlturaTela - player.Altura) {
        player.Y = AlturaTela - player.Altura;
    }

}

void InputPlayer2() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {

        player2.Y = player2.Y - player2.Velocidade;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player2.Y = player2.Y + player2.Velocidade;
    }

    if (player2.Y < 0) {
        player2.Y = 0;
    }
    else if (player2.Y > AlturaTela - player2.Altura) {
        player2.Y = AlturaTela - player2.Altura;
    }

}

void Inputs() {
    InputPlayer1();
    InputPlayer2();
}

bool ColisaoPlayerBola()
{
    return player.X < bola.X + bola.Largura &&
        player.X + player.Largura > bola.X &&
        player.Y < bola.Y + bola.Altura &&
        player.Y + player.Altura > bola.Y;
}

bool ColisaoPlayer2Bola()
{
    return player2.X < bola.X + bola.Largura &&
        player2.X + player2.Largura > bola.X &&
        player2.Y < bola.Y + bola.Altura &&
        player2.Y + player2.Altura > bola.Y;
}

void Logica() {
    Inputs();

    bola.X += bola.Velocidade * bola.DirecaoX;
    bola.Y += bola.Velocidade * bola.DirecaoY;

    if (bola.Y < 0)
    {
        bola.Y = 0;
        bola.DirecaoY *= -1;
    }
    else if (bola.Y > AlturaTela - bola.Altura)
    {
        bola.Y = AlturaTela - bola.Altura;
        bola.DirecaoY *= -1;
    }

    if (ColisaoPlayerBola()) {
        bola.X = LarguraTela - 24;
        bola.DirecaoX *= -1;
    }
    else if (ColisaoPlayer2Bola()) {
        bola.X = 16;
        bola.DirecaoX *= -1;
        
    }

    if (bola.X < 0) {
        PontosPlayer2++;
        bola = Novabola;
        bola.DirecaoX = 1;
    }
    else if (bola.X > LarguraTela - bola.Largura) {
        PontosPlayer++;
        bola = Novabola;
        bola.DirecaoX = -1;
    }
}

void InputPause() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Pause = !Pause;
    }
}
        
void DesenharPlacar() {
    DesenharTexto(std::to_string(PontosPlayer), 57, 63, 100, Grey);
    DesenharTexto(std::to_string(PontosPlayer2), 257, 63, 100, Grey);
}

int main()
{
    window.setFramerateLimit(60);
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.clear(sf::Color::Black);
        InputPause();
        if (!Pause) {
            Logica();
        }
        DesenharPlacar();
        DesenharPlayer();
        DesenharPlayer2();
        DesenharBola();
        
        window.display();
    }

    return 0;
}