#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;
template <typename T>
class SortingSystem {
private:
    T* data;
    int size;
    int iteration=1;

public:
    void sortInsertion() { insertionSort(data, size); }
    void sortSelection() { selectionSort(data, size); }
    void sortBubble() { bubbleSort(data, size); }
    void sortShell() { shellSort(data, size); }
    void sortMerge() { mergeSort(data, 0, size-1); }
    void sortQuick() { quickSort(data, 0, size-1); }
    void sortCount() { countsort(data, size); } // For integers only
    void sortRadix() { radixSort(data, size); } // For integers only
    void sortBucket() { bucketSort(data, size); }
    // Constructor
    SortingSystem(int n){
        size = n;
        data = new T[n];
    }
    // Destructor
    ~SortingSystem(){
        delete[] data;
    }
    //Function to take input from user
    void TakeInput(){
        cout<<"Enter the data to sort:"<<endl;
        for(int i =0 ;i < size ;i++){
            cin>>data[i];
        }
    }

    void EnterDataFromFile(T arr[]){
        for(int i =0 ;i < size ;i++){
            data[i] = arr[i];
        }
    }
    //(1) Insertion Sort
    void insertionSort(T arr[], int n){
        T key;
        int j;
        for (int i = 1 ;i < n ;i++){
            key=arr[i];
            j=i-1;
            while(j>=0 && arr[j]>key ){
                arr[j+1]=arr[j];
                j=j-1;
            }
            arr[j+1]=key;
            cout<<"Iteration "<<i<<":";
            displayData();

        }
    }
    //(2) Selection Sort
    void selectionSort(T arr[],int n){
        for (int i=0;i<n-1;i++){
            int minimum=i;
            for(int j=i+1; j<n ;j++){
                if (arr[j]<arr[minimum]){
                    minimum=j;
                }
            }
            swap(arr[i],arr[minimum]);
            cout<<"Iteration "<<i+1<<":";
            displayData();
        }
    }
    //(3) Bubble Sort
    void bubbleSort(T arr[], int n){
        for(int i=0;i<n-1;i++){
            for(int j=0 ; j<n-i-1 ;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                }
            }
            cout<<"Iteration "<<i+1<<":";
            displayData();
        }
    }
    //(4) Shell Sort
    void shellSort(T arr[] , int n){
        for (int gap = n / 2; gap > 0; gap /= 2) {
            cout<<"Iteration "<<iteration++ << " (gap=" << gap << "): ";
            for (int i = gap; i < n; i++) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
            displayData();
        }
    }
    //(5) Merge Sort
    void mergeSort(T arr[],int left, int right){
        if(left<right){
            int mid=left+(right-left)/2;
            cout << "Iteration " << iteration++ << ": Split ";
            displaySubarray(left, right);
            cout << " -> ";
            displaySubarray(left, mid);
            cout << " | ";
            displaySubarray(mid+1, right);
            cout << endl;
            mergeSort(arr,left,mid);
            mergeSort(arr,mid+1,right);
            merge(arr,left,mid,right);
        }
    }
    //(6) Quick Sort
    void quickSort(T arr[], int left, int right){
        if(left >= right)
            return;
        else{
            int pivot=partition(arr,left,right );
            quickSort(arr,left,pivot-1);
            quickSort(arr,pivot+1,right);
        }
    }
    //(7) Count Sort (Only for int)
    void countsort(int arr[], int n){
        int maxElement= arr[0];
        int B_array[n]={0};
        int* C_array = new int [maxElement+1];
        // Find the largest element of the array
        for (int i = 1; i < n; i++) {
            if (arr[i] > maxElement)
                maxElement = arr[i];
        }
        cout << "Max element: " << maxElement << endl << endl;
        cout << "Initialized count array (size " << maxElement+1 << "): ";

        // Initialize C array with all zeros.
        for (int i = 0; i <= maxElement; ++i) {
            C_array[i] = 0;
            cout << C_array[i] << " ";
        }
        cout<<endl;
        // Store the count of each element
        cout << "Counting phase:" << endl;
        for (int i = 0; i < n; i++) {
            C_array[arr[i]]++;
            cout << "After counting " << arr[i] << ": ";
            for (int j = 0; j <= maxElement; j++) {
                cout << C_array[j] << " ";
            }
            cout << endl;
        }
        cout<<endl;
        // Store the cummulative count of each C_array
        cout << "Cumulative counts:" << endl;
        for (int i = 1; i <= maxElement; i++) {
            C_array[i] += C_array[i - 1];
            cout << "After position " << i << ": ";
            for (int j = 0; j <= maxElement; j++) {
                cout << C_array[j] << " ";
            }
            cout<<endl;
        }
        cout<<endl;
        // Find the index of each element of the original array in C_array, and
        // place the elements in B_array
        cout << "Building sorted array:" << endl;
        for (int i = n - 1; i >= 0; i--) {
            B_array[C_array[arr[i]] - 1] = arr[i];
            C_array[arr[i]]--;
            cout << "Placed " << arr[i] << " at position " << C_array[arr[i]] << ": [";
            for (int j = 0; j < n; j++) {
                cout <<B_array[j] << " ";

            }
            cout << "]" << endl;
        }
        for (int i = 0; i < n; i++) {
            arr[i] = B_array[i];
        }
        displayData();
        delete [] C_array;

    }
    //(8) Radix Sort (Only for int)
    void radixSort(int arr[], int n){
        int maxElement = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > maxElement)
                maxElement = arr[i];
        // Apply counting sort to sort elements based on place value.
        for (int place = 1; maxElement / place > 0; place *= 10){
            countSortForRadix(arr, n, place);
            cout << "Sorting on " << place << "'s digit: ";
            displayData();
        }
    }
    //(9) Bucket Sort
    void bucketSort(T arr[], int n) {
        // Only allow bucket sort for numeric types
        static_assert(is_arithmetic<T>::value, "Bucket sort requires numeric types");
        // Create buckets
        T buckets[n][n] ;
        int counts[n] = {0}; // Initialize all counts to 0
        // Find max element
        T maxElement = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > maxElement) {
                maxElement = arr[i];
            }
        }
        cout << "Max Element: " << maxElement << endl;
        cout << "Distributing elements into buckets:" << endl;
        // Put elements in buckets
        for (int i = 0; i < n; i++) {
            // Normalize value to [0,1) range
            double normalizedValue = static_cast<double>(arr[i]) / (maxElement + 1);
            int bucketIndex = static_cast<int>(normalizedValue * n);
            // Add to bucket
            buckets[bucketIndex][counts[bucketIndex]] = arr[i];
            counts[bucketIndex]++;
            // Print bucket status
            cout << "Element " << arr[i] << " -> Bucket " << bucketIndex << ": [";
            for (int j = 0; j < counts[bucketIndex]; j++) {
                cout << buckets[bucketIndex][j] << " ";
            }
            cout << "]" << endl;
        }
        cout << "Sorting individual buckets:" << endl;
        // Sort individual buckets
        for (int i = 0; i < n; i++) {
            if (counts[i] > 0) {
                cout << "Sorting Bucket " << i << ": [";
                for (int j = 0; j < counts[i]; j++) {
                    cout << buckets[i][j] << " ";
                }
                cout << "] -> ";

                // Sort the bucket
                insertionSort(buckets[i], counts[i]);
                cout << "[";
                for (int j = 0; j < counts[i]; j++) {
                    cout << buckets[i][j] << " ";
                }
                cout << "]" << endl;
            }
        }
        // Concatenate all buckets into arr[]
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < counts[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
        displayData();
    }
    //Helper methods
    // Merge Sort Helper
    void merge(T arr[],int left, int mid, int right){
        int i,j,k;
        int n1=mid-left+1;
        int n2=right-mid;
        T* L = new T[n1];
        T* R = new T[n2];
        T* originalLeft = new T[n1]; //to store original left sub array before merge
        T* originalRight = new T[n2]; //to store original right sub array before merge
        for(i=0;i<n1;i++){
            L[i]=arr[left+i];
            originalLeft[i] = arr[left + i];
        }
        for(j=0;j<n2;j++){
            R[j]=arr[mid+1+j];
            originalRight[j] = arr[mid + 1 + j];
        }
        i=j=0;
        k=left;
        while (i<n1&&j<n2){
            if(L[i]<=R[j]){
                arr[k]=L[i];
                i++;
            }
            else{
                arr[k]=R[j];
                j++;
            }
            k++;
        }
        while(i < n1){
            arr[k]=L[i];
            i++;
            k++;
        }
        while(j < n2){
            arr[k]=R[j];
            j++;
            k++;
        }
        cout << "Merge [";
        for (int x = 0; x < n1; x++) {
            cout << originalLeft[x];
            if (x < n1-1) {
                cout << ",";
            }
        }
        cout << "] + [";
        for (int x = 0; x < n2; x++) {
            cout << originalRight[x];
            if (x < n2-1){
                cout << ",";
            }
        }
        cout << "] -> [";
        for (int x = left; x <= right; x++) {
            cout << arr[x];
            if (x < right){
                cout << ",";
            }
        }
        cout << "]" << endl;

        delete[] L;
        delete[] R;
        delete[] originalLeft;
        delete[] originalRight;
    }
    // Quick Sort Helper
    int partition(T arr[], int low, int high){
        int i=low;
        for(int j =low+1;j<=high;j++){
            if(arr[j]< arr[low] ){
                i++;
                swap(arr[i],arr[j]);
            }
        }
        swap(arr[i],arr[low]);
        cout << "Pivot: " << arr[i] << " -> ";
        if(low <= i-1) {
            displaySubarray(low, i-1);
        } else {
            cout << "[]";
        }
        cout << " " << arr[i] << " ";
        if(i+1 <= high) {
            displaySubarray(i+1, high);
        } else {
            cout << "[]";
        }
        cout << endl;

        return i;
    }
    //Radix Sort Helper
    void countSortForRadix(int arr[], int n, int place) {
        int B_array[n];
        int C_array[10]={0};

        for (int i = 0; i < n; ++i)
            C_array[i] = 0;
        for (int i = 0; i < n; i++)
            C_array[(arr[i] / place) % 10]++;
        for (int i = 1; i <10; i++)
            C_array[i] += C_array[i - 1];
        // Place the elements in sorted order
        for (int i = n - 1; i >= 0; i--) {
            B_array[C_array[(arr[i] / place) % 10] - 1] = arr[i];
            C_array[(arr[i] / place) % 10]--;
        }
        for (int i = 0; i < n; i++)
            arr[i] = B_array[i];
    }
    //Function to display step by step iterations in merge sort
    void displaySubarray(int start, int end) {
        cout << "[";
        for (int i = start; i <= end; i++) {
            cout << data[i];
            if (i < end) cout << ",";
        }
        cout << "]";
    }
    // Print the current state of the array
    void displayData(){
        T* currentState = new T[size];
        copy(data, data + size, currentState);

        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << currentState[i];
            if (i < size - 1) {
                cout << " ";
            }
        }
        cout << "]";
        cout << endl;

        delete[] currentState;
    }
    void measureSortTime(void (SortingSystem::* sortFunc)()) {
        // Make a copy of the original data to preserve it
        T* originalData = new T[size];
        copy(data, data + size, originalData);
        // Start the timer
        auto start = chrono::high_resolution_clock::now();
        // Call the sorting function
        (this->*sortFunc)();
        // Stop the timer
        auto stop = chrono::high_resolution_clock::now();
        // Calculate duration with explicit casting
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << endl;
        cout << "Sorted Array: ";
        displayData();
        // Restore the original data
        copy(originalData, originalData + size, data);
        // Convert to seconds with decimal precision
        double seconds = duration.count() / 1000000.0;

        // Display the formatted time
        cout << "Sorting Time: ";
        printf("%.5f seconds\n", seconds);
        delete[] originalData;
    }
    // Display menu for user interaction
    void showMenu(){
        cout<<"Select a sorting algorithm(1-10): "<<endl;
        cout<<"1. Insertion Sort" <<endl;
        cout<<"2. Selection Sort" <<endl;
        cout<<"3. Bubble Sort" <<endl;
        cout<<"4. Shell Sort" <<endl;
        cout<<"5. Merge Sort" <<endl;
        cout<<"6. Quick Sort" <<endl;
        cout<<"7. Count Sort (Only for integers)" <<endl;
        cout<<"8. Radix Sort (Only for integers)" <<endl;
        cout<<"9. Bucket Sort " <<endl;

    }

    // Function to read an integer number within a specific range
    int ReadNumber(int From, int To, int SpecialAllowed, string ErrorMessage) {
        int Number;
        do {
            cin >> Number;
            // Check if the input is a valid integer
            if (cin.good()) {
                // Ensure that there are no trailing characters
                if (cin.peek() == '\n') {
                    // Check if number is in normal range OR equals the special allowed number
                    if ((Number >= From && Number <= To) || Number == SpecialAllowed) {
                        return Number;
                    }
                }
            }
            // If input is invalid, clear error flags and ignore the remaining input
            cin.clear();
            cin.ignore(256, '\n');

            cout << ErrorMessage << endl;

        } while (true);
    }

};


int main()
{
    bool EndProgram = false;
    do {
        cout << "Select input source:" << endl;
        cout << "1. Console input" << endl;
        cout << "2. File input" << endl;
        int source;
        do {
            cin >> source;
            if (cin.fail() || source < 1 || source > 2) {
                cin.clear(); // Clear error flag
                cin.ignore(256, '\n'); // Discard invalid input
                cout << "Invalid input. Enter a valid input: ";
            } else if (cin.peek() != '\n') { // Ensure no extra input
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid input. Enter a valid input: ";
            } else {
                break; // Valid input, exit loop
            }
        } while (true);

        switch (source) {
            case 1: {
                int n;
                cout << "Enter the number of items to sort: ";
                while (true) {
                    cin >> n;
                    // Check if the input is an integer
                    if (cin.fail() || n <= 0) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(256, '\n'); // Discard invalid input
                        cout << "Invalid input! Please enter a positive integer.\n";
                    } else
                        break;
                }

                cout << "Select the data type (1-6):" << endl;
                cout << "1. String" << endl;
                cout << "2. Character" << endl;
                cout << "3. Integer" << endl;
                cout << "4. Float" << endl;
                cout << "5. Double" << endl;

                int datatype;
                do {
                    cin >> datatype;
                    if (cin.fail() || source < 1 || source > 2) {
                        cin.clear(); // Clear error flag
                        cin.ignore(256, '\n'); // Discard invalid input
                        cout << "Invalid input. Enter a valid input: ";
                    } else if (cin.peek() != '\n') { // Ensure no extra input
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Invalid input. Enter a valid input: ";
                    } else {
                        break; // Valid input, exit loop
                    }
                } while (true);

                switch (datatype) {
                    // String
                    case 1: {
                        SortingSystem<string> StringSorting(n);
                        StringSorting.TakeInput();
                        StringSorting.showMenu();

                        int Choice = StringSorting.ReadNumber(1, 6, 6,
                                                              "Invalid sorting choice for string datatype. Enter a valid choice:");

                        switch (Choice) {
                            case 1:
                                StringSorting.measureSortTime(&SortingSystem<string>::sortInsertion);
                                break;
                            case 2:
                                StringSorting.measureSortTime(&SortingSystem<string>::sortSelection);
                                break;
                            case 3:
                                StringSorting.measureSortTime(&SortingSystem<string>::sortBubble);
                                break;
                            case 4:
                                StringSorting.measureSortTime(&SortingSystem<string>::sortShell);
                                break;
                            case 5:
                                StringSorting.measureSortTime(&SortingSystem<string>::sortMerge);
                                break;
                            case 6:
                                StringSorting.measureSortTime(&SortingSystem<string>::sortQuick);
                                break;
                            default:
                                cout << "Invalid sorting choice!" << endl;
                        }
                        cout << endl << endl;
                        break;
                    }
                        // Character
                    case 2: {
                        SortingSystem<char> CharSorting(n);
                        CharSorting.TakeInput();
                        CharSorting.showMenu();

                        int Choice = CharSorting.ReadNumber(1, 6, 6,
                                                            "Invalid sorting choice for character datatype. Enter a valid choice:");

                        switch (Choice) {
                            case 1:
                                CharSorting.measureSortTime(&SortingSystem<char>::sortInsertion);
                                break;
                            case 2:
                                CharSorting.measureSortTime(&SortingSystem<char>::sortSelection);
                                break;
                            case 3:
                                CharSorting.measureSortTime(&SortingSystem<char>::sortBubble);
                                break;
                            case 4:
                                CharSorting.measureSortTime(&SortingSystem<char>::sortShell);
                                break;
                            case 5:
                                CharSorting.measureSortTime(&SortingSystem<char>::sortMerge);
                                break;
                            case 6:
                                CharSorting.measureSortTime(&SortingSystem<char>::sortQuick);
                                break;
                            default:
                                cout << "Invalid sorting choice!" << endl;
                        }
                        cout << endl << endl;
                        break;
                    }
                        // Integer
                    case 3: {
                        SortingSystem<int> IntSorting(n);
                        IntSorting.TakeInput();
                        IntSorting.showMenu();

                        int Choice = IntSorting.ReadNumber(1, 9, 9, "Invalid input. Enter a valid input:");

                        switch (Choice) {
                            case 1:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortInsertion);
                                break;
                            case 2:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortSelection);
                                break;
                            case 3:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortBubble);
                                break;
                            case 4:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortShell);
                                break;
                            case 5:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortMerge);
                                break;
                            case 6:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortQuick);
                                break;
                            case 7:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortBucket);
                                break;
                            case 8:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortCount);
                                break;
                            case 9:
                                IntSorting.measureSortTime(&SortingSystem<int>::sortRadix);
                                break;
                            default:
                                cout << "Invalid sorting choice!" << endl;
                        }
                        cout << endl << endl;
                        break;
                    }
                        // Float
                    case 4: {
                        SortingSystem<float> FloatSorting(n);
                        FloatSorting.TakeInput();
                        FloatSorting.showMenu();

                        int Choice = FloatSorting.ReadNumber(1, 6, 9, "Invalid sorting choice for float datatype. Enter a valid choice:");

                        switch (Choice) {
                            case 1:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortInsertion);
                                break;
                            case 2:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortSelection);
                                break;
                            case 3:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortBubble);
                                break;
                            case 4:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortShell);
                                break;
                            case 5:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortMerge);
                                break;
                            case 6:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortQuick);
                                break;
                            case 9:
                                FloatSorting.measureSortTime(&SortingSystem<float>::sortBucket);
                                break;
                            default:
                                cout << "Invalid sorting choice!" << endl;
                        }
                        cout << endl << endl;
                        break;
                    }
                        // Double
                    case 5: {
                        SortingSystem<double> DoubleSorting(n);
                        DoubleSorting.TakeInput();
                        DoubleSorting.showMenu();

                        int Choice = DoubleSorting.ReadNumber(1, 6, 9, "Invalid sorting choice for double datatype. Enter a valid choice:");

                        switch (Choice) {
                            case 1:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortInsertion);
                                break;
                            case 2:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortSelection);
                                break;
                            case 3:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortBubble);
                                break;
                            case 4:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortShell);
                                break;
                            case 5:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortMerge);
                                break;
                            case 6:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortQuick);
                                break;
                            case 9:
                                DoubleSorting.measureSortTime(&SortingSystem<double>::sortBucket);
                                break;
                            default:
                                cout << "Invalid sorting choice!" << endl;
                        }
                        cout << endl << endl;
                        break;
                    }
                    default:
                        cout << "Invalid data type selected!" << endl;
                        break;
                }
                break;
            }
            case 2: {
                string filename;
                cout << "Enter the filename containing test cases: ";
                cin >> filename;

                ifstream inputFile(filename);
                if (!inputFile.is_open()) {
                    cout << "Error: Could not open file!" << endl;
                    break;
                }

                int n;
                string datatype;
                getline(inputFile, datatype);
                inputFile >> n;

                if (datatype == "string"){
                    SortingSystem<string> StringSorting(n);
                    string arr[n];
                    for (int i = 0; i < n; ++i) {
                        inputFile >> arr[i];
                    }
                    StringSorting.EnterDataFromFile(arr);
                    cout << "Sorting using Insertion Sort:\n";
                    StringSorting.measureSortTime(&SortingSystem<string>::sortInsertion);
                    cout << "\n\nSorting using Selection Sort:\n";
                    StringSorting.measureSortTime(&SortingSystem<string>::sortSelection);
                    cout << "\n\nSorting using Bubble Sort:\n";
                    StringSorting.measureSortTime(&SortingSystem<string>::sortBubble);
                    cout << "\n\nSorting using Shell Sort:\n";
                    StringSorting.measureSortTime(&SortingSystem<string>::sortShell);
                    cout << "\n\nSorting using Merge Sort:\n";
                    StringSorting.measureSortTime(&SortingSystem<string>::sortMerge);
                    cout << "\n\nSorting using Quick Sort:\n";
                    StringSorting.measureSortTime(&SortingSystem<string>::sortQuick);
                }

                else if (datatype == "char"){
                    SortingSystem<char> CharSorting(n);
                    char arr[n];
                    for (int i = 0; i < n; ++i) {
                        inputFile >> arr[i];
                    }
                    CharSorting.EnterDataFromFile(arr);
                    cout << "Sorting using Insertion Sort:\n";
                    CharSorting.measureSortTime(&SortingSystem<char>::sortInsertion);
                    cout << "\n\nSorting using Selection Sort:\n";
                    CharSorting.measureSortTime(&SortingSystem<char>::sortSelection);
                    cout << "\n\nSorting using Bubble Sort:\n";
                    CharSorting.measureSortTime(&SortingSystem<char>::sortBubble);
                    cout << "\n\nSorting using Shell Sort:\n";
                    CharSorting.measureSortTime(&SortingSystem<char>::sortShell);
                    cout << "\n\nSorting using Merge Sort:\n";
                    CharSorting.measureSortTime(&SortingSystem<char>::sortMerge);
                    cout << "\n\nSorting using Quick Sort:\n";
                    CharSorting.measureSortTime(&SortingSystem<char>::sortQuick);
                }

                else if (datatype == "int") {
                    SortingSystem<int> IntSorting(n);
                    int arr[n];
                    for (int i = 0; i < n; ++i) {
                        inputFile >> arr[i];
                    }
                    IntSorting.EnterDataFromFile(arr);
                    cout << "Sorting using Insertion Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortInsertion);
                    cout << "\n\nSorting using Selection Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortSelection);
                    cout << "\n\nSorting using Bubble Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortBubble);
                    cout << "\n\nSorting using Shell Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortShell);
                    cout << "\n\nSorting using Merge Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortMerge);
                    cout << "\n\nSorting using Quick Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortQuick);
                    cout << "\n\nSorting using Count Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortCount);
                    cout << "\n\nSorting using Radix Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortRadix);
                    cout << "\n\nSorting using Bucket Sort:\n";
                    IntSorting.measureSortTime(&SortingSystem<int>::sortBucket);
                }

                else if (datatype == "float"){
                    SortingSystem<float> FloatSorting(n);
                    float arr[n];
                    for (int i = 0; i < n; ++i) {
                        inputFile >> arr[i];
                    }
                    FloatSorting.EnterDataFromFile(arr);
                    cout << "Sorting using Insertion Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortInsertion);
                    cout << "\n\nSorting using Selection Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortSelection);
                    cout << "\n\nSorting using Bubble Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortBubble);
                    cout << "\n\nSorting using Shell Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortShell);
                    cout << "\n\nSorting using Merge Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortMerge);
                    cout << "\n\nSorting using Quick Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortQuick);
                    cout << "\n\nSorting using Bucket Sort:\n";
                    FloatSorting.measureSortTime(&SortingSystem<float>::sortBucket);
                }

                else if (datatype == "double"){
                    SortingSystem<double> DoubleSorting(n);
                    double arr[n];
                    for (int i = 0; i < n; ++i) {
                        inputFile >> arr[i];
                    }
                    DoubleSorting.EnterDataFromFile(arr);
                    cout << "Sorting using Insertion Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortInsertion);
                    cout << "\n\nSorting using Selection Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortSelection);
                    cout << "\n\nSorting using Bubble Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortBubble);
                    cout << "\n\nSorting using Shell Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortShell);
                    cout << "\n\nSorting using Merge Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortMerge);
                    cout << "\n\nSorting using Quick Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortQuick);
                    cout << "\n\nSorting using Bucket Sort:\n";
                    DoubleSorting.measureSortTime(&SortingSystem<double>::sortBucket);
                }
                inputFile.close();
            }
        }

        cout << "\nDo you want to sort another dataset? (y/n):";
        char ContinueOrNot;
        do {
            cin >> ContinueOrNot;
            if(ContinueOrNot == 'y' || ContinueOrNot == 'Y'){
                cout << endl;
                break;
            }
            else if(ContinueOrNot == 'n' || ContinueOrNot == 'N'){
                EndProgram = true;
                cout << "\nThanks for using Sorting System. Goodbye!";
                break;
            }
            else{
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid input. Enter (y/n):";
            }
        } while (true);

    } while (!EndProgram);
    return 0;
}