#include "matrixProcessing.h"

std::vector< std::vector<float> >read_probtrackx2_matrix( std::string inputMatrixTextFile )
{
    std::string fileName = inputMatrixTextFile;
    std::ifstream inputFile ;
    inputFile.open( fileName.c_str() , std::ios::in ) ;

    std::vector< std::string > mat_string;
    std::vector< std::string >::const_iterator mat_it,mat_end;
    std::string labelLine;

    //Catch each row of the matrix in a vector of string
    if(inputFile.good())
    {
        do
        {
            getline( inputFile , labelLine ) ; //get information line
        }while( labelLine[0] == '#' ) ;

        while(!inputFile.eof())
        {
            if(labelLine.empty() !=true )
            {
                mat_string.push_back(labelLine);
            }
            getline(inputFile,labelLine);
        }
    }
    inputFile.close();

    //Number of row
    int nb_lines=mat_string.size();
    std::cout<<"Number of rows : "<<nb_lines<<std::endl;

    std::vector< std::vector <std::string> > mat;
    std::string::const_iterator s_it, s_end ;

    std::vector< std::vector<float> > mat_num;

    //Find each matrix components
    for(mat_it=mat_string.begin() , mat_end=mat_string.end() ; mat_it!=mat_end ; ++mat_it)
    {
        std::string line = *mat_it;
        std::vector< std::string > cells;
        std::string number;

        for(s_it=line.begin() , s_end=line.end() ; s_it!=s_end ; ++s_it)
        {
            if(*s_it != ' ')
            {
                number += *s_it ;
                if(s_it == s_end-1)  //if last character is a number
                {
                    cells.push_back(number);
                    number.clear();
                }
            }
            else
            {
                if( number != "")
                {
                    cells.push_back(number);
                    number.clear();
                }
                else
                {
                    //Catch next char
                }
            }
        }
        //Verified that is a square matrix
        if(cells.size() != nb_lines)
        {
            std::cout<<"Error : dimension of matrix not matched - Matrix should be square "<<std::endl;
            mat_num.clear();
            return mat_num;
        }
        else
        {
            mat.push_back(cells);

        }
        cells.clear();
    }
    std::cout<<"Matrix dimension verified "<<nb_lines<<"x"<<nb_lines<<std::endl;


    //Convert matrix of string with matrix of double
    for(int i = 0 ; i < nb_lines ; i++)
    {
        std::vector<float>  row_num;
        for(int j = 0 ; j < nb_lines ; j++)
        {
            std::string component = mat[i][j];
            double num_component = atoi( component.c_str() );
            row_num.push_back(num_component);

        }
        mat_num.push_back(row_num);
    }
    return mat_num;
}

template<typename T>
void print_matrix(std::vector< std::vector<T> > matrix)
{
    std::cout<<"Matrix : "<<std::endl;
    //Print matrix
    typename std::vector< std::vector <T> >::const_iterator row_it, row_end;

    for(row_it=matrix.begin() , row_end=matrix.end() ; row_it!=row_end ; ++row_it)
    {
        typename std::vector< T > row = *row_it;
        typename std::vector <T>::const_iterator column_it, column_end;
        for(column_it=row.begin() , column_end=row.end() ; column_it!=column_end ; ++column_it)
        {
            T val = *column_it;
            std::cout<<val<<" ";
        }
        std::cout<<""<<std::endl;
    }
}

template<typename T>
void print_vector( std::vector<T>  vector)
{
    std::cout<<"Vector :"<<std::endl;
    //Print vector
    typename  std::vector <T>::const_iterator row_it, row_end;

    for(row_it=vector.begin() , row_end=vector.end() ; row_it!=row_end ; ++row_it)
    {
        T row = *row_it;
        std::cout<<row<<" ";
    }
}

void write_matrixFile(std::vector< std::vector<float> >  matrix , std::string filename)
{
    std::string filenameOutput=filename;
    std::ofstream outputFile ;
    std::vector< std::vector <float> >::const_iterator row_it, row_end;

    outputFile.open( filenameOutput.c_str() , std::ios::out ) ;
    if( outputFile.good() )
    {
        for(row_it=matrix.begin() , row_end=matrix.end() ; row_it!=row_end ; ++row_it)
        {
            std::vector< float > row = *row_it;
            std::vector <float>::const_iterator column_it, column_end;
            std::string line="";

            for(column_it=row.begin() , column_end=row.end() ; column_it!=column_end ; ++column_it)
            {
                float val = *column_it;
                line += FloatToString(val);
                if(column_it != column_end-1)
                {
                    line += " ";
                }
            }
            line += "\n";
            outputFile << line ;
        }
    }
    outputFile.close() ;
    std::cout<<"File created : "<<filename<<std::endl;

}

std::string FloatToString ( float number )
{
    std::string result ;
    std::ostringstream convert ;
    convert << number ;
    result = convert.str() ;
    return result ;
}

std::vector< std::vector<float> >  normalized_matrix( std::vector< std::vector<float> > matrix )
{
    std::vector<float> waytotal ;
    std::vector< std::vector <float> >::const_iterator row_it, row_end;

    std::vector< std::vector<float> > mat_num ;

    int id = 0;
    for( int k=0 ; k < 2 ; k++ )
    {
        for(row_it=matrix.begin() , row_end=matrix.end() ; row_it!=row_end ; ++row_it)
        {
            std::vector< float > row = *row_it;
            std::vector <float>::const_iterator column_it, column_end;

            float total=0;
            float val_norm = 0.0f;
            std::vector<float> row_float ;

            for(column_it=row.begin() , column_end=row.end() ; column_it!=column_end ; ++column_it)
            {
                if(k==0)
                {
                    total += *column_it;
                }
                else
                {
                    int val = *column_it;
                    val_norm = val/waytotal.at(id);
                    row_float.push_back(val_norm);
                }
            }
            if(k==0)
            {
                waytotal.push_back(total);
            }
            else
            {
                mat_num.push_back(row_float);
                id++;
            }
        }
    }

    std::cout<<"waytotal_size : "<<waytotal.size()<<std::endl;
    return mat_num;
}

std::vector< std::vector<float> > maximumConnectivity ( std::vector< std::vector<float> > matrix )
{
    //Find max
    std::vector< std::vector <float> > maxConnectivity;
    int nb_lines=matrix.size();

    for(int i = 0 ; i < nb_lines ; i++)
    {
        std::vector<float> rows;
        for(int j = 0 ; j <nb_lines ; j++)
        {
            if(i==j)
            {
                rows.push_back(0);
            }
            else if (j>i)
            {
                if( matrix[i][j] > matrix[j][i] )
                {
                rows.push_back(matrix[i][j]);
                }
                else
                {
                rows.push_back(matrix[j][i]);
                }
            }
            else
            {
                rows.push_back(0);
            }
        }
        maxConnectivity.push_back(rows);
    }
        return maxConnectivity ;
}

std::vector< std::vector<float> > minimumConnectivity ( std::vector< std::vector<float> > matrix )
{
    //Find min
    std::vector< std::vector <float> > minConnectivity;

    int nb_lines=matrix.size();

    for(int i = 0 ; i < nb_lines ; i++)
    {
        std::vector<float> rows;
        for(int j = 0 ; j <nb_lines ; j++)
        {
            if(i==j)
            {
                rows.push_back(0);
            }
            else if (j>i)
            {
                if( matrix[i][j] < matrix[j][i] )
                {
                rows.push_back(matrix[i][j]);
                }
                else
                {
                rows.push_back(matrix[j][i]);
                }
            }
            else
            {
                rows.push_back(0);
            }
        }
        minConnectivity.push_back(rows);
    }
        return minConnectivity ;
}

std::vector< std::vector<float> > averageConnectivity ( std::vector< std::vector<float> > matrix )
{
    //Find min
    std::vector< std::vector <float> > minConnectivity;
    int nb_lines=matrix.size();

    for(int i = 0 ; i < nb_lines ; i++)
    {
        std::vector<float> rows;
        for(int j = 0 ; j <nb_lines ; j++)
        {
            if(i==j)
            {
                rows.push_back(0);
            }
            else if (j>i)
            {
                float average;
                average = (matrix[i][j] + matrix[j][i]) / 2 ;
                rows.push_back(average);
            }
            else
            {
                rows.push_back(0);
            }
        }
        minConnectivity.push_back(rows);
    }
        return minConnectivity ;
}




int main ( int argc, char *argv[] )
{

    PARSE_ARGS;

    if(normalized == 0 && triangularMatrixMaximumValue == 0 && triangularMatrixMinimumValue == 0 && triangularMatrixAverageValue == 0)
    {
        std::cout << "Nothing to do. Specified at leat one action (--normalized or --max or --min or --average )" << std::endl ;
        return EXIT_FAILURE ;
    }
    else
    {
        std::vector< std::vector <float> > matrix;
        matrix = read_probtrackx2_matrix(inputMatrixTextFile);
        if(matrix.empty() == true)
        {
        std::cout<<"Error - verified matrix dimension "<<std::endl;
        return EXIT_FAILURE;
        }
        if( normalized == 1 )
        {
            std::vector< std::vector <float> > matrix_norm;
            matrix_norm=normalized_matrix(matrix);
            write_matrixFile(matrix_norm,outputNormalizedFilename);
        }
        if ( useMatrixNormalized == 1 && (triangularMatrixMaximumValue == 1 || triangularMatrixMinimumValue == 1 || triangularMatrixAverageValue == 1))
        {
            std::vector< std::vector <float> > matrix_norm;
            matrix_norm=normalized_matrix(matrix);

            if(triangularMatrixMaximumValue == 1)
            {
                std::vector< std::vector <float> > matrixMax;
                matrixMax = maximumConnectivity(matrix_norm);
                std::string filename = "Maximum_Normalized_" + outputTriangularMatrixFilename;
                write_matrixFile(matrixMax,filename);

            }
            if(triangularMatrixMinimumValue == 1)
            {
                std::vector< std::vector <float> > matrixMin;
                matrixMin = minimumConnectivity(matrix_norm);
                std::string filename = "Minimum_Normalized_" + outputTriangularMatrixFilename;
                write_matrixFile(matrixMin,filename);

            }
            if(triangularMatrixAverageValue == 1)
            {
                std::vector< std::vector <float> > matrixAverage;
                matrixAverage = averageConnectivity(matrix_norm);
                std::string filename = "Average_Normalized_" + outputTriangularMatrixFilename;
                write_matrixFile(matrixAverage,filename);
            }
        }
        else if (useMatrixNormalized == 0 && (triangularMatrixMaximumValue == 1 || triangularMatrixMinimumValue == 1 || triangularMatrixAverageValue == 1))
        {
            if(triangularMatrixMaximumValue == 1)
            {
                std::vector< std::vector <float> > matrixMax;
                matrixMax = maximumConnectivity(matrix);
                std::string filename = "Maximum_" + outputTriangularMatrixFilename;
                write_matrixFile(matrixMax,filename);

            }
            if(triangularMatrixMinimumValue == 1)
            {
                std::vector< std::vector <float> > matrixMin;
                matrixMin = minimumConnectivity(matrix);
                std::string filename = "Minimun_" + outputTriangularMatrixFilename;
                write_matrixFile(matrixMin,filename);

            }
            if(triangularMatrixAverageValue == 1)
            {
                std::vector< std::vector <float> > matrixAverage;
                matrixAverage = averageConnectivity(matrix);
                std::string filename = "Average_" + outputTriangularMatrixFilename;
                write_matrixFile(matrixAverage,filename);
            }
        }
    }
    return EXIT_SUCCESS;

}
