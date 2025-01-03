#include<stdio.h>
#include<string.h>

struct Patient {
    char name[50];
    int age;
    char disease[50];
    char doctorAssigned[50];
};

struct Doctor {
    char name[50];
    char specialization[50];
    int availability; // 1 = available, 0 = unavailable
};

void addpatient() {
    struct Patient s;
    printf("Enter details of patient\n");
    
    // Reading name with spaces
    printf("Name: ");
    getchar();  // To clear any leftover newline character
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  // Remove trailing newline
    
    printf("Age: ");
    scanf("%d", &s.age);
    
    // Reading disease with spaces
    printf("Disease: ");
    getchar();  // To clear any leftover newline character
    fgets(s.disease, sizeof(s.disease), stdin);
    s.disease[strcspn(s.disease, "\n")] = '\0';  // Remove trailing newline
    
    strcpy(s.doctorAssigned, "None");

    FILE *ptr = fopen("patients.txt", "a");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(ptr, "%s,\t%d,\t%s,\t%s;\n", s.name, s.age, s.disease, s.doctorAssigned);
    fclose(ptr);

    printf("Patient added successfully!\n");
}

void viewpatient() {
    printf("This is the data of all patients:\n");
    FILE *ptr = fopen("patients.txt", "r");
    if (ptr == NULL) {
        printf("No patient records found!\n");
        return;
    }

    char ch[100];
    while (fgets(ch, 100, ptr) != NULL) {
        printf("%s", ch);
    }
    fclose(ptr);
}

void adddoctor() {
    struct Doctor d;
    printf("Enter details of doctor\n");

    // Reading name with spaces
    printf("Name: ");
    getchar();  // To clear any leftover newline character
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = '\0';  // Remove trailing newline
    
    // Reading specialization with spaces
    printf("Specialization: ");
    fgets(d.specialization, sizeof(d.specialization), stdin);
    d.specialization[strcspn(d.specialization, "\n")] = '\0';  // Remove trailing newline
    
    d.availability = 1;

    FILE *ptr = fopen("doctors.txt", "a");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(ptr, "%s,\t%s,\t%d;\n", d.name, d.specialization, d.availability);
    fclose(ptr);

    printf("Doctor added successfully!\n");
}

void viewdoctor() {
    printf("This is the data of all doctors:\n");
    FILE *ptr = fopen("doctors.txt", "r");
    if (ptr == NULL) {
        printf("No doctor records found!\n");
        return;
    }

    char ch[100];
    while (fgets(ch, 100, ptr) != NULL) {
        printf("%s", ch);
    }
    fclose(ptr);
}

void assigndoc() {
    // Step 1: Select a patient
    FILE *patientFile = fopen("patients.txt", "r");
    if (patientFile == NULL) {
        printf("No patient records found!\n");
        return;
    }

    char patients[100][200];
    int patientIndex = 0;
    printf("Select a patient to assign a doctor:\n");
    while (fgets(patients[patientIndex], sizeof(patients[patientIndex]), patientFile) != NULL) {
        printf("%d. %s", patientIndex + 1, patients[patientIndex]);
        patientIndex++;
    }
    fclose(patientFile);

    if (patientIndex == 0) {
        printf("No patients available to assign a doctor.\n");
        return;
    }

    int selectedPatient;
    printf("Enter the patient number: ");
    scanf("%d", &selectedPatient);
    if (selectedPatient < 1 || selectedPatient > patientIndex) {
        printf("Invalid selection.\n");
        return;
    }
    selectedPatient--; // Convert to zero-based index

    // Step 2: Select a doctor
    FILE *doctorFile = fopen("doctors.txt", "r");
    if (doctorFile == NULL) {
        printf("No doctor records found!\n");
        return;
    }

    char doctors[100][200];
    int doctorIndex = 0;
    printf("Select a doctor to assign to the patient:\n");
    while (fgets(doctors[doctorIndex], sizeof(doctors[doctorIndex]), doctorFile) != NULL) {
        char name[50], specialization[50];
        int availability;
        sscanf(doctors[doctorIndex], "%[^,], %[^,], %d", name, specialization, &availability);
        if (availability == 1) {
            printf("%d. %s (%s)\n", doctorIndex + 1, name, specialization);
        }
        doctorIndex++;
    }
    fclose(doctorFile);

    if (doctorIndex == 0) {
        printf("No available doctors.\n");
        return;
    }

    int selectedDoctor;
    printf("Enter the doctor number: ");
    scanf("%d", &selectedDoctor);
    if (selectedDoctor < 1 || selectedDoctor > doctorIndex) {
        printf("Invalid selection.\n");
        return;
    }
    selectedDoctor--; // Convert to zero-based index

    // Step 3: Update patient record
    FILE *tempPatientFile = fopen("temp_patients.txt", "w");
    patientFile = fopen("patients.txt", "r");
    char buffer[200];
    int currentIndex = 0;
    while (fgets(buffer, sizeof(buffer), patientFile) != NULL) {
        if (currentIndex == selectedPatient) {
            struct Patient p;
            sscanf(buffer, "%[^,], %d, %[^,], %[^;]", p.name, &p.age, p.disease, p.doctorAssigned);
            sscanf(doctors[selectedDoctor], "%[^,],", p.doctorAssigned);
            fprintf(tempPatientFile, "%s,\t%d,\t%s,\t%s;\n", p.name, p.age, p.disease, p.doctorAssigned);
        } else {
            fputs(buffer, tempPatientFile);
        }
        currentIndex++;
    }
    fclose(patientFile);
    fclose(tempPatientFile);
    remove("patients.txt");
    rename("temp_patients.txt", "patients.txt");

    // Step 4: Update doctor record
    FILE *tempDoctorFile = fopen("temp_doctors.txt", "w");
    doctorFile = fopen("doctors.txt", "r");
    currentIndex = 0;
    while (fgets(buffer, sizeof(buffer), doctorFile) != NULL) {
        if (currentIndex == selectedDoctor) {
            struct Doctor d;
            sscanf(buffer, "%[^,], %[^,], %d", d.name, d.specialization, &d.availability);
            d.availability = 0;
            fprintf(tempDoctorFile, "%s,\t%s,\t%d;\n", d.name, d.specialization, d.availability);
        } else {
            fputs(buffer, tempDoctorFile);
        }
        currentIndex++;
    }
    fclose(doctorFile);
    fclose(tempDoctorFile);
    remove("doctors.txt");
    rename("temp_doctors.txt", "doctors.txt");

    printf("Doctor assigned successfully!\n");
}

int main() {
    int ch;
    do {
        printf("\nMenu\n");
        printf("1. Add Patient Record\n");
        printf("2. View Patient Records\n");
        printf("3. Add Doctor Record\n");
        printf("4. View Doctor Records\n");
        printf("5. Assign Doctor\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                addpatient();
                break;
            case 2:
                viewpatient();
                break;
            case 3:
                adddoctor();
                break;
            case 4:
                viewdoctor();
                break;
            case 5:
                assigndoc();
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (ch != 6);

    return 0;
}
