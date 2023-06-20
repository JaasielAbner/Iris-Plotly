#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_POINTS 150
#define MAX_LINE_LENGTH 100

typedef struct
{
    float x;
    float y;
    float z;
    float w;
    int pos;
} Point;

typedef struct
{
    Point points[MAX_POINTS];
    int count;
} ClassPoints;

void parseCSVLine(char *line, Point *point)
{
    char *token;
    token = strtok(line, ",");
    point->x = atof(token);
    token = strtok(NULL, ",");
    point->y = atof(token);
    token = strtok(NULL, ",");
    point->z = atof(token);
    token = strtok(NULL, ",");
    point->w = atof(token);
}

void sortByClassSize(ClassPoints *classPoints, int classCount)
{
    for (int i = 1; i <= classCount; i++)
    {
        for (int j = 1; j <= classCount - i - 1; j++)
        {
            if (classPoints[j].count > classPoints[j + 1].count)
            {
                ClassPoints temp = classPoints[j];
                classPoints[j] = classPoints[j + 1];
                classPoints[j + 1] = temp;
            }
        }
    }
}

void clusterizeClasses(ClassPoints *classPoints, int classCount)
{
    while (classCount > 3)
    {

        int smallestClassIdx = 1;
        for (int i = 1; i <= classCount; i++)
        {
            if (classPoints[i].count < classPoints[smallestClassIdx].count)
            {
                smallestClassIdx = i;
            }
        }

        int largestClassIndices[3] = {0};
        int largestCounts[3] = {0};

        for (int i = 1; i <= classCount; i++)
        {
            if (classPoints[i].count > largestCounts[0])
            {
                largestCounts[2] = largestCounts[1];
                largestClassIndices[2] = largestClassIndices[1];
                largestCounts[1] = largestCounts[0];
                largestClassIndices[1] = largestClassIndices[0];
                largestCounts[0] = classPoints[i].count;
                largestClassIndices[0] = i;
            }
            else if (classPoints[i].count > largestCounts[1])
            {
                largestCounts[2] = largestCounts[1];
                largestClassIndices[2] = largestClassIndices[1];
                largestCounts[1] = classPoints[i].count;
                largestClassIndices[1] = i;
            }
            else if (classPoints[i].count > largestCounts[2])
            {
                largestCounts[2] = classPoints[i].count;
                largestClassIndices[2] = i;
            }
        }

        Point averagePoints[3];
        for (int i = 0; i < 3; i++)
        {
            ClassPoints *class = &classPoints[largestClassIndices[i]];
            float sumX = 0, sumY = 0, sumZ = 0, sumW = 0;
            for (int j = 0; j < class->count; j++)
            {
                sumX += class->points[j].x;
                sumY += class->points[j].y;
                sumZ += class->points[j].z;
                sumW += class->points[j].w;
            }
            int classSize = class->count;
            averagePoints[i].x = sumX / classSize;
            averagePoints[i].y = sumY / classSize;
            averagePoints[i].z = sumZ / classSize;
            averagePoints[i].w = sumW / classSize;
        }

        for (int i = 0; i < classPoints[smallestClassIdx].count; i++)
        {
            Point point = classPoints[smallestClassIdx].points[i];
            int nearestClassIdx = 0;
            float minDistance = INFINITY;
            for (int j = 1; j <= 3; j++)
            {
                float distance = sqrt(pow(point.x - averagePoints[j].x, 2) +
                                      pow(point.y - averagePoints[j].y, 2) +
                                      pow(point.z - averagePoints[j].z, 2) +
                                      pow(point.w - averagePoints[j].w, 2));
                if (distance < minDistance)
                {
                    nearestClassIdx = largestClassIndices[j];
                    minDistance = distance;
                }
            }
            classPoints[nearestClassIdx].points[classPoints[nearestClassIdx].count] = point;
            classPoints[nearestClassIdx].count++;
        }

        classPoints[smallestClassIdx] = classPoints[classCount];
        classCount--;
    }
}

void redistributePoints(ClassPoints *classPoints, int classCount)
{
    int counter = 0;
    while ((classPoints[1].count > 50 || classPoints[2].count > 50 || classPoints[3].count > 50) && counter<150 )
    {
        for (int i = 1; i <= classCount; i++)
        {
            while (classPoints[i].count > 50)
            {
                Point center;
                float sumX = 0, sumY = 0, sumZ = 0, sumW = 0;
                for (int j = 0; j < classPoints[i].count; j++)
                {
                    sumX += classPoints[i].points[j].x;
                    sumY += classPoints[i].points[j].y;
                    sumZ += classPoints[i].points[j].z;
                    sumW += classPoints[i].points[j].w;
                }
                int classSize = classPoints[i].count;
                center.x = sumX / classSize;
                center.y = sumY / classSize;
                center.z = sumZ / classSize;
                center.w = sumW / classSize;

                int furthestPos = 0;
                float furthestDistance = 0;

                for (int j = 0; j < classPoints[i].count; j++)
                {
                    Point point = classPoints[i].points[j];
                    float distance = sqrt(pow(point.x - center.x, 2) +
                                          pow(point.y - center.y, 2) +
                                          pow(point.z - center.z, 2) +
                                          pow(point.w - center.w, 2));
                    if (distance > furthestDistance)
                    {
                        furthestDistance = distance;
                        furthestPos = j;
                    }
                }
                Point furthest = classPoints[i].points[furthestPos];
                int closestClusterIdx = -1;
                float minDistance = INFINITY;

                for (int k = 1; k <= classCount; k++)
                {
                    if (k != i)
                    {
                        Point clusterCenter;
                        sumX = 0, sumY = 0, sumZ = 0, sumW = 0;

                        for (int l = 0; l < classPoints[k].count; l++)
                        {
                            sumX += classPoints[k].points[l].x;
                            sumY += classPoints[k].points[l].y;
                            sumZ += classPoints[k].points[l].z;
                            sumW += classPoints[k].points[l].w;
                        }
                        classSize = classPoints[k].count;
                        clusterCenter.x = sumX / classSize;
                        clusterCenter.y = sumY / classSize;
                        clusterCenter.z = sumZ / classSize;
                        clusterCenter.w = sumW / classSize;
                        float dist = sqrt(pow(furthest.x - clusterCenter.x, 2) +
                                          pow(furthest.y - clusterCenter.y, 2) +
                                          pow(furthest.z - clusterCenter.z, 2) +
                                          pow(furthest.w - clusterCenter.w, 2));
                        if (dist < minDistance)
                        {
                            closestClusterIdx = k;
                            minDistance = dist;
                        }
                    }
                }

                classPoints[closestClusterIdx].points[classPoints[closestClusterIdx].count] = furthest;
                classPoints[closestClusterIdx].count++;

                for (int k = furthestPos; k <= classPoints[i].count; k++)
                {
                    classPoints[i].points[k] = classPoints[i].points[k + 1];
                }
                classPoints[i].count--;
            }
        }
        counter++;
    }
}

int main()
{
    FILE *csvFile = fopen("IrisDataset.csv", "r");
    FILE *txtFile = fopen("classes.txt", "r");

    if (csvFile == NULL || txtFile == NULL)
    {
        printf("Failed to open input files.\n");
        return 1;
    }

    ClassPoints classPoints[MAX_POINTS];
    int classCount = 1;

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), csvFile);
    int pos = 1;
    while (fgets(line, sizeof(line), txtFile) != NULL)
    {
        int classId = atoi(line);
        if (classId > classCount)
            classCount = classId;

        Point point;
        fgets(line, sizeof(line), csvFile);
        parseCSVLine(line, &point);
        point.pos = pos++;

        ClassPoints *class = &classPoints[classId];
        class->points[class->count] = point;
        class->count++;
    }

    fclose(csvFile);
    fclose(txtFile);

    sortByClassSize(classPoints, classCount);

    clusterizeClasses(classPoints, classCount);
    classCount = 3;

    redistributePoints(classPoints, classCount);

    for (int i = 1; i <= classCount; i++)
    {
        printf("Class %d:\n", i);
        ClassPoints *class = &classPoints[i];
        for (int j = 0; j < class->count; j++)
        {
            Point point = class->points[j];
            printf("%.2f, %.2f, %.2f, %.2f\n", point.x, point.y, point.z, point.w);
            // printf("%d: %.2f, %.2f, %.2f, %.2f\n", point.pos, point.x, point.y, point.z, point.w);
        }
    }

    return 0;
}
