#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include "matrixProcessingCLP.h"

std::vector< std::vector<float> > read_probtrackx2_matrix( std::string inputMatrixTextFile );

std::vector< std::vector<float> >  normalized_matrix( std::vector< std::vector<float> > matrix );

template<typename T>
void print_matrix(std::vector< std::vector<T> > matrix);

template<typename T>
void print_vector( std::vector<T>  vector);

void write_matrixFile(std::vector< std::vector<float> >  vector, std::string filename);

std::string FloatToString ( float number );

std::vector< std::vector<float> > maximumConnectivity (std::vector< std::vector<float> > matrix );

std::vector< std::vector<float> > minimumConnectivity (std::vector< std::vector<float> > matrix );

std::vector< std::vector<float> > averageConnectivity (std::vector< std::vector<float> > matrix );
