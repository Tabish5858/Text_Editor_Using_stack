#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

using namespace std;

class TextEditor
{
private:
    string text;
    stack<string> undoStack;
    stack<string> redoStack;
    int cursorPosition;

public:
    TextEditor()
    {
        cursorPosition = 0;
    }

    void insert(char c)
    {
        try
        {
            text.insert(cursorPosition, 1, c);
            undoStack.push(text);
            cursorPosition++;
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void deleteChar()
    {
        try
        {
            if (cursorPosition > 0 && cursorPosition <= text.length())
            {
                text.erase(cursorPosition - 1, 1);
                undoStack.push(text);
                cursorPosition--;
            }
            else
            {
                throw out_of_range("Cannot delete character. Invalid cursor position.");
            }
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void next()
    {
        try
        {
            if (cursorPosition < text.length())
            {
                cursorPosition++;
            }
            else
            {
                throw out_of_range("Cannot move cursor to next position. Already at the end of the text.");
            }
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void previous()
    {
        try
        {
            if (cursorPosition > 0)
            {
                cursorPosition--;
            }
            else
            {
                throw out_of_range("Cannot move cursor to previous position. Already at the beginning of the text.");
            }
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void start()
    {
        try
        {
            cursorPosition = 0;
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void end()
    {
        try
        {
            cursorPosition = text.length();
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    int curr_position()
    {
        return cursorPosition;
    }

    void undo()
    {
        try
        {
            if (!undoStack.empty())
            {
                redoStack.push(undoStack.top());
                undoStack.pop();

                if (undoStack.size() > 5)
                {
                    undoStack.pop();
                }

                if (!undoStack.empty())
                {
                    text = undoStack.top();
                }
                else
                {
                    text = "";
                }

                cursorPosition = text.length();
            }
            else
            {
                throw runtime_error("Cannot undo. No more undo operations available.");
            }
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void redo()
    {
        try
        {
            if (!redoStack.empty())
            {
                text = redoStack.top();
                undoStack.push(redoStack.top());
                redoStack.pop();

                if (undoStack.size() > 5)
                {
                    undoStack.pop();
                }

                cursorPosition = text.length();
            }
            else
            {
                throw runtime_error("Cannot redo. No more redo operations available.");
            }
            printText();
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void printText()
    {
        cout << "Current text: " << text << endl;
        cout << "Cursor position: " << cursorPosition << endl;
    }
};

int main()
{
    TextEditor editor;
    char choice;
    do
    {
        cout << "1. Insert a character" << endl;
        cout << "2. Delete a character" << endl;
        cout << "3. Next" << endl;
        cout << "4. Previous" << endl;
        cout << "5. Start" << endl;
        cout << "6. End" << endl;
        cout << "7. Current position" << endl;
        cout << "8. Undo" << endl;
        cout << "9. Redo" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            char c;
            cout << "Enter a character: ";
            cin >> c;
            editor.insert(c);
            break;
        case '2':
            editor.deleteChar();
            break;
        case '3':
            editor.next();
            break;
        case '4':
            editor.previous();
            break;
        case '5':
            editor.start();
            break;
        case '6':
            editor.end();
            break;
        case '7':
            cout << "Current position: " << editor.curr_position() << endl;
            break;
        case '8':
            editor.undo();
            break;
        case '9':
            editor.redo();
            break;
        case '0':
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);

    return 0;
}
