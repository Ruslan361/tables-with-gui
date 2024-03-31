#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QAbstractItemModel>
#include <sstream>
#include <QMessageBox>


std::vector<std::string> SplitPolynom(const std::string& polynom)
{
    std::vector<std::string> monoms;
    std::string current;
    for (char c : polynom)
    {
        if((c == '+'))
        {
            //std::cout << current << '\n';
            monoms.push_back(current);
            current = "";
        }
        else if (c == '-')
        {
            //std::cout << current << '\n';
            monoms.push_back(current);
            current = "-";
        }
        else
        {
            current += c;
        }
    }
    monoms.push_back(current);
    //std::cout << current;
    return monoms;
}

Monom<int> MonomFromString(std::string monom, const std::vector<std::string>& names_of_variables)
{
    if(monom == "")
        throw std::invalid_argument("monom must be not empty");
    int mul = 1;
    if (monom[0] == '-')
    {
        mul = -1;
        monom.erase(0,1);
    }
    size_t size = monom.size();

    int coeff = 0;
    std::vector<int> degrees(names_of_variables.size());
    std::fill(degrees.begin(), degrees.end(), 0);


    int i = 0;
    while (isdigit(monom[i]) && i < monom.size())
    {
        coeff *= 10;
        coeff += int(monom[0] - '0');
        i++;
    }
    if (!isdigit(monom[0]))
        coeff = 1;

    std::string current;
    for (; i < monom.size(); i++)
    {
        current += monom[i];
        auto it = find(names_of_variables.begin(), names_of_variables.end(), current);
        if (it != names_of_variables.end())
        {
            int index = it - names_of_variables.begin();
            if ((i+2 < monom.size()) && (monom[i+1] == '^') && isdigit(monom[i+2]))
            {
                degrees[index] = monom[i+2] - '0';
                i+=2;
            }
            else
            {
                degrees[index] = 1;
            }
            current = "";
        }
    }
    if (!current.empty())
        throw std::invalid_argument("something went wrong");
    /*
    std::cout << coeff << std::endl;
    for (int d : degrees)
    {
        std::cout << d << '\n';
    }
    */
    return Monom<int>(coeff, degrees);
}

Polynom<int> PolynomFromString(const std::string& polynom, const std::vector<std::string> names_of_variables)
{
    TSingleLinkedList<Monom<int>> list_monom;
    std::vector<std::string> monoms = SplitPolynom(polynom);
    for (size_t i = 0; i < monoms.size(); i++)
    {
        list_monom.Add(MonomFromString(monoms[i], names_of_variables));
    }
    return Polynom<int>(list_monom, names_of_variables);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Tables tables;
    ui->SelectTableComboBox->addItems(tables.names);
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddBtn_clicked()
{
    int key = ui->spinBox->value();
    QString text = ui->lineEdit->text();
    std::string convert_text = text.toStdString();
    std::vector<std::string> variables = {"x", "y", "z"};

    try{
        Polynom<int> pol = PolynomFromString(convert_text, variables);
        tables.Add(tables.mode, key, pol);
    }
    catch(std::out_of_range ex)
    {
        QMessageBox::about(this, "Ошибка ввода", ex.what());
    }
    catch(std::invalid_argument ex)
    {
        QMessageBox::about(this, "Ошибка ввода", ex.what());
    }


    RefreshTable(tables.mode);
}


void MainWindow::RefreshTable(int index)
{
    ui->tableWidget->setRowCount(0);
    TSingleLinkedList<int> keys = tables.GetKeys(index);

    for(auto it = keys.begin(); it != keys.end(); ++it)
    {
        Polynom<int> result;
        if(tables.Search(index, (*it), result))
        {
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(rowCount + 1);

            std::string polynom_text;
            std::ostringstream ostr;
            ostr << result;
            polynom_text = ostr.str();

            QTableWidgetItem * items[] = {
                new QTableWidgetItem(QString::number(*it)),
                new QTableWidgetItem(QString::fromStdString(polynom_text))
            };
            const size_t count = sizeof(items) / sizeof(QTableWidgetItem*);
            for (size_t column = 0; column < count; ++column)
            {
                ui->tableWidget->setItem(rowCount, column, items[column]);
            }

            //ui->tableWidget->setCellWidget(rowCount, 2, )
        }
    }
}

void MainWindow::on_SelectTableComboBox_currentIndexChanged(int index)
{

    tables.mode = index;
    RefreshTable(index);
    //QAbstractItemModel*
    //ui->tableView->setModel();
}


void MainWindow::on_RemBtn_clicked()
{
    int key = ui->RemoveSpinBox->value();
    tables.Remove(tables.mode, key);
    RefreshTable(tables.mode);
}

