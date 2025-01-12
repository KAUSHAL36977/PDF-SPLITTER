#include <podofo/podofo.h>
#include <iostream>
#include <string>
#include <filesystem>

void splitPDF(const std::string& inputPath, const std::string& outputDir, int pagesPerSplit) {
    try {
        PoDoFo::PdfMemDocument inputPdf(inputPath.c_str());
        int totalPages = inputPdf.GetPageCount();
        int splitCount = (totalPages + pagesPerSplit - 1) / pagesPerSplit;

        for (int i = 0; i < splitCount; ++i) {
            PoDoFo::PdfMemDocument outputPdf;
            int startPage = i * pagesPerSplit;
            int endPage = std::min(startPage + pagesPerSplit, totalPages);

            for (int j = startPage; j < endPage; ++j) {
                outputPdf.Append(inputPdf.GetPage(j));
            }

            std::string outputFile = outputDir + "/split_" + std::to_string(i + 1) + ".pdf";
            outputPdf.Write(outputFile.c_str());
            std::cout << "Created: " << outputFile << std::endl;
        }
        std::cout << "PDF splitting complete." << std::endl;
    } catch (const PoDoFo::PdfError& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
}

int main() {
    std::string inputPdfPath = "input.pdf";       // Path to the input PDF file
    std::string outputDirectory = "./output";    // Directory to save the split PDFs
    int pagesPerFile = 5;                        // Number of pages per split

    // Ensure output directory exists
    if (!std::filesystem::exists(outputDirectory)) {
        std::filesystem::create_directories(outputDirectory);
    }

    splitPDF(inputPdfPath, outputDirectory, pagesPerFile);
    return 0;
}
