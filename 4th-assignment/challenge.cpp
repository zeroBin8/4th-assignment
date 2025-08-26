#include <iostream>
#include <vector>
#include <string>
#include <map>

// PotionRecipe Ŭ����: ��� ����� vector<string>���� ����
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // ���� ��ῡ�� ��� '���'���� ����

    // ������: ��� ����� �޾� �ʱ�ȭ�ϵ��� ����
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop Ŭ����: ������ ����� ����
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe �޼���: ��� ���(vector)�� �Ű������� �޵��� ����
    //�����ͷ� ����
    PotionRecipe* addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> ���ο� ������ '" << name << "'��(��) �߰��Ǿ����ϴ�.\n" << std::endl;
        
        return &recipes.back(); //���� �������� ���� �����Ǹ� ��ȯ�ؼ� �ٷ� ��� ����
    }

    // ��� ������ ��� �޼���
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "���� ��ϵ� �����ǰ� �����ϴ�." << std::endl;
            return;
        }

        std::cout << "\n--- [ ��ü ������ ��� ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- ���� �̸�: " << recipes[i].potionName << std::endl;
            std::cout << "  > �ʿ� ���: ";

            // ��� ����� ��ȸ�ϸ� ���
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // ������ ��ᰡ �ƴϸ� ��ǥ�� ����
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n" << std::endl;
    }

    //���� �̸����� ã��
    //�����ͷ� ����
    PotionRecipe* searchRecipeByName(const std::string& name)
    {
        for (auto& recipe : recipes)
        {
            if (recipe.potionName == name)
            {
                return &recipe;
            }
        }

        return nullptr;
    }

    //���� ��� �̸����� �˻�, ��ᰡ ���Ե� ��� ���� ã��
    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient)
    {
        std::vector<PotionRecipe> result;

        for (PotionRecipe n : recipes)
        {
            for (std::string i : n.ingredients)
            {
                if (i == ingredient)
                {
                    result.push_back(n);
                    break;
                }
            }
        }

        return result;
    }

    //��� �����Ǹ� ���ͷ� ��ȯ
    const std::vector<PotionRecipe>& getAllRecipes() { return recipes; }

};

class StockManager
{
private:
    std::map<std::string, int> potionStock;
    const int Max_Stock = 3;

public:
    void initializeStock(std::string potionName)
    {
        potionStock[potionName] = Max_Stock; //���� ������ �߰��� �⺻���� 3�� �߰� 
    }

    bool dispensePotion(const std::string& potionName) {
        auto it = potionStock.find(potionName); // Ű �˻�

        if (it != potionStock.end())            //���� �˻�
        {           
            if (it->second > 0)                 // ��� Ȯ��
            {               
                std::cout <<"\n"<< potionName << " ���� 1�� ����\n" << std::endl;
                it->second--;                    // ��� ����
                return true;
            }
            else 
            {
                std::cout << "\n������ ������ �����մϴ�.\n" << std::endl;
                return false;
            }
        }
        else 
        {
            std::cout << "\n�ش� ������ �������� �ʽ��ϴ�.\n" << std::endl;
            return false;
        }
    }


    void returnPotion(std::string potionName) //������ ���� ���� �ޱ�, ������ ������ ������ �����ϰ� �Լ� ȣ���ؼ� ���� �ޱ�?
    {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end()) {
            if (it->second < Max_Stock) { // ��� �ִ�ġ���� ������
                it->second++;
                std::cout << "\n" << potionName << " ���� 1�� ��ȯ �Ϸ�\n";
                std::cout << "���� ������ ����: " << potionStock[potionName] <<"\n"<< std::endl;
            }
            else {
                std::cout <<"\n"<< potionName << " ������ ��� �̹� �ִ�ġ�Դϴ�. ��ȯ �Ұ�.\n" << std::endl;
            }
        }
        else {
            std::cout << "�ش� ������ �������� �ʾ� ��ȯ�� �� �����ϴ�.\n" << std::endl;
        }
    }

    int getStock(std::string potionName) //���� ���� Ȯ��
    {
        return potionStock[potionName];
    }
};


int main() {
    AlchemyWorkshop myWorkshop;
    StockManager stockManager;

    while (true) {
        std::cout << "**���ݼ� ���� ���� �ý���**" << std::endl;
        std::cout << "1. ������ �߰�" << std::endl;
        std::cout << "2. ��� ������ ���" << std::endl;
        std::cout << "3. �̸����� �˻�" << std::endl;
        std::cout << "4. ��� �̸����� �˻�" << std::endl;
        std::cout << "5. ��� �˻�" << std::endl;
        std::cout << "6. ���� ����" << std::endl;
        std::cout << "7. ���� ��ȯ" << std::endl;
        std::cout << "8. ����" << std::endl;
        std::cout << "����: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "���� �̸�: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // ���� ��Ḧ �Է¹ޱ� ���� ����
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "�ʿ��� ������ �Է��ϼ���. (�Է� �Ϸ� �� '��' �Է�)" << std::endl;

            while (true) {
                std::cout << "��� �Է�: ";
                std::getline(std::cin, ingredient);

                // ����ڰ� '��'�� �Է��ϸ� ��� �Է� ����
                if (ingredient == "��") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // �Է¹��� ��ᰡ �ϳ� �̻� ���� ���� ������ �߰�
            // ��� �߰�
            if (!ingredients_input.empty()) 
            {
                PotionRecipe* newRecipe =  myWorkshop.addRecipe(name, ingredients_input);
                stockManager.initializeStock(newRecipe->potionName);
            }
            else {
                std::cout << ">> ��ᰡ �Էµ��� �ʾ� ������ �߰��� ����մϴ�." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) //���� �̸����� �˻�
        {
            std::string name;
            std::cout << "\n���� �̸��� �Է��ϼ���: ";
            std::cin >> name;
            
            //nullptr ��ȯ�� ���� ������ ���

            if (myWorkshop.searchRecipeByName(name) == nullptr)
            {
                std::cout << "\n������ �������� �ʽ��ϴ�.\n" << std::endl;
            }
            else
            {
                std::cout << myWorkshop.searchRecipeByName(name)->potionName  << " ������ �����մϴ�\n" << std::endl;
            }
            

        }
        else if (choice == 4)
        {
            std::string ingredient;
            std::cout << "\n��� �̸��� �Է��ϼ���: ";
            std::cin >> ingredient;

            std::cout << "\n�˻��� ��Ḧ �����ϴ� ����: ";

            for (PotionRecipe n : myWorkshop.searchRecipeByIngredient(ingredient))
            {
                std::cout << n.potionName << " ";
            }
            std::cout << "\n" << std::endl;
        }
        else if (choice == 5) //��� �˻�
        {
            std::string name;

            std::cout << "\n�˻��� ���� �̸�: ";
            std::cin >> name;

            std::cout << "\n���� �̸�: " << name << "\n���: " << stockManager.getStock(name) <<"\n" << std::endl;
        }
        else if (choice == 6) //���� ����
        {
            std::string name;

            std::cout << "������ ������ �����ϼ���: ";
            std::cin >> name;

            if (stockManager.dispensePotion(name))
            {
                std::cout << "���� ���� ����\n";
                std::cout << "���� ������ ����: " << stockManager.getStock(name) <<"\n"<< std::endl;
            }
            else
            {
                std::cout << "���� ���� ����\n" << std::endl;
            }
        }
        else if (choice == 7) //���� ��ȯ
        {
            std::string name;

            std::cout << "��ȯ�� ������ �����ϼ���: ";
            std::cin >> name;

            stockManager.returnPotion(name);
        }
        else if (choice == 8) {
            std::cout << "���� ���� �ݽ��ϴ�..." << std::endl;
            break;

        }
        else {
            std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
        }
    }

    return 0;
}