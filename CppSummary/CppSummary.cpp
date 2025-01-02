#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book
{
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author)
    {
    }
};

class BookManager
{
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author)
    {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const
    {
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++)
        { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    /// <summary>
    /// 없으면 nullptr 반환
    /// </summary>
    Book* getBookByTitle(const string& title)
    {
        for (auto& book : books)
        {
            if (book.title == title)
            {
                return &book;
            }
        }

        return nullptr;
    }

    /// <summary>
    /// 없으면 nullptr 반환
    /// </summary>
    Book* getBookByAuthor(const string& author)
    {
        for (auto& book : books)
        {
            if (book.author == author)
            {
                return &book;
            }
        }

        return nullptr;
    }
};

class BorrowManager
{
private:
    std::unordered_map<string, int> stock;

    int maxStock = 3;

public:

    void initializeStock(const Book& book, int quantity = 3)
    {
        if (getBookStockCount(book.title) == -1)
        {
            stock.insert(make_pair(book.title, quantity));
        }
        else
        {
            stock[book.title] = quantity;
        }
    }

    void borrowBook(const string& title)
    {
        int stockCount = getBookStockCount(title);
        if (stockCount == -1)
        {
            cout << "저희 도서관에 \"" << title << '\"' << "(이)라는 책은 없습니다." << endl;
            return;
        }

        if (stockCount <= 0)
        {
            cout << '\"' << title << '\"' << "은(는) 재고가 다 떨어졌습니다." << endl;
            return;
        }

        stock[title]--;
        cout << '\"' << title << '\"' << "을(를) 빌렸습니다." << endl;
    }

    void returnBook(const string& title)
    {
        int stockCount = getBookStockCount(title);
        if (stockCount == -1)
        {
            cout << "저희 도서관에 \"" << title << '\"' << "(이)라는 책은 없습니다... 저희 도서관 책이 아닌 거 같은데요?" << endl;
            return;
        }

        if (stockCount >= maxStock)
        {
            cout << '\"' << title << '\"' << "은(는) 대여 중인 것이 없는데, 저희 도서관 책이 아닌 거 같은데요?" << endl;
            return;
        }

        stock[title]++;
        cout << '\"' << title << '\"' << "을(를) 반납했습니다." << endl;
    }

    void displayAllStocks() const
    {
        cout << "현재 재고 : ";

        if (stock.empty())
        {
            cout << "없음" << endl;
            return;
        }

        for (const auto& s : stock)
        {
            cout << s.first << ' ' << s.second << "개, ";
        }
    }

    /// <returns>존재했던 적이 없으면 -1 반환</returns>
    int getBookStockCount(const string& title)
    {
        if (stock.find(title) == stock.end())
        {
            return -1;
        }

        return stock[title];
    }
};

class LibraryManager
{
private:

    BookManager bookManager;
    BorrowManager borrowManager;

public:

    void addBook(const string& title, const string& author)
    {
        bookManager.addBook(title, author);
        borrowManager.initializeStock(Book(title, author));
    }

    void displayAllBooks() const
    {
        bookManager.displayAllBooks();
    }

    void displayAllStocks() const
    {
        borrowManager.displayAllStocks();
    }

    void searchBookByTitle(const string& title)
    {
        Book* book = bookManager.getBookByTitle(title);
        if (book == nullptr)
        {
            cout << title << "(이)라는 책은 없습니다." << endl;
            return;
        }

        displayBookInfo(*book);
    }

    void searchBookByAuthor(const string& author)
    {
        Book* book = bookManager.getBookByAuthor(author);
        if (book == nullptr)
        {
            cout << author << "의 책은 없습니다." << endl;
            return;
        }

        displayBookInfo(*book);
    }

    void borrowBook(const string& title)
    {
        borrowManager.borrowBook(title);
    }

    void returnBook(const string& title)
    {
        borrowManager.returnBook(title);
    }

private:

    void displayBookInfo(const Book& book)
    {
        cout << "┌────────── 책 정보──────────" << endl;
        cout << "│ 제목 : " << book.title << endl;
        cout << "│ 저자 : " << book.author << endl;
        cout << "│ 재고 : " << borrowManager.getBookStockCount(book.title) << endl;
        cout << "└────────────────────────────" << endl;
    }
};

int main()
{
    LibraryManager manager;
    //BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true)
    {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 검색" << endl;
        cout << "4. 작가 검색" << endl;
        cout << "5. 책 대여" << endl;
        cout << "6. 책 반납" << endl;
        cout << "7. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1)
        {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2)
        {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3번 선택 : 책 검색
            string title;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.searchBookByTitle(title);
        }
        else if (choice == 4)
        {
            // 4번 선택 : 작가 검색
            string author;
            cout << "책 저자: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 제목 입력 (공백 포함)
            manager.searchBookByAuthor(author);

        }
        else if (choice == 5)
        {
            // 5번 선택 : 책 대여
            string title;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.borrowBook(title);

        }
        else if (choice == 6)
        {
            // 6번 선택 : 책 반납
            string title;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.returnBook(title);
        }
        else if (choice == 7)
        {
            // 7번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else
        {
            // 잘못된 입력 처리
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
