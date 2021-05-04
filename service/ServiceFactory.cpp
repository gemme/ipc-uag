#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

struct PService {
  char const  *enterprise_department;
  char const  *name;
  char const  *city;
  char const  *address;
};

struct SService{
    char const  *government_department;
    char const  *name;
    char const  *city;
    char const  *address;
};

class Service {

  public:
  virtual char* getService(SService ss){ return NULL; };
  virtual char* getService(PService ss){ return NULL; };
  virtual char* getServices() = 0;

};

class ProfessionalService: public Service {

  public:

  ProfessionalService(){
    printf("Professional service constructor \n");
  }

  char *getService(struct PService ss){
    char *_professional_service = (char*)malloc(1024);
    strcpy(_professional_service, "\n enterprise_department: ");
    strcat(_professional_service, ss.enterprise_department);
    strcat(_professional_service, "\n name : ");
    strcat(_professional_service, ss.name);
    strcat(_professional_service, "\n city : ");
    strcat(_professional_service, ss.city);
    strcat(_professional_service, "\n address : ");
    strcat(_professional_service, ss.address);
    strcat(_professional_service, "\n");
    return _professional_service;
  }
  char *getServices(){
    struct PService p1 = { "Finance", "Oracle", "Guadalajara", "Av. niños heroes 123" };
    struct PService p2 = { "Networks", "Google", "California", "Mountain View" };
    struct PService p3 = { "Systems", "Improving", "Guadalajara", "Av. Lazaro Cardenas 123" };
    char *response = (char*)malloc(1024);
    strcat(response, "\n");
    strcat(response, getService(p1));
    strcat(response, "\n");
    strcat(response, getService(p2));
    strcat(response, "\n");
    strcat(response, getService(p3));
    strcat(response, "\n");
    return response;
  }

};
class SocialService: public Service {

  public:

  SocialService(){
    printf("Social service constructor \n");
  }

  char *getService(struct SService ss){
    char *_social_service = (char*)malloc(1024);
    strcpy(_social_service, "\n goverment department: ");
    strcat(_social_service, ss.government_department);
    strcat(_social_service, "\n name : ");
    strcat(_social_service, ss.name);
    strcat(_social_service, "\n city : ");
    strcat(_social_service, ss.city);
    strcat(_social_service, "\n address : ");
    strcat(_social_service, ss.address);
    strcat(_social_service, "\n");
    return _social_service;
  }
  char *getServices(){
    struct SService s1 = { "Finance", "SHCP", "Guadalajara", "Av. niños heroes 123" };
    struct SService s2 = { "Human Resources", "SAT", "Guadalajara", "Av. Lopez Mateos 654" };
    struct SService s3 = { "Systems", "INEGI", "Guadalajara", "Av. Lazaro Cardenas 123" };
    char *response = (char*)malloc(1024);
    strcat(response, "\n");
    strcat(response, getService(s1));
    strcat(response, "\n");
    strcat(response, getService(s2));
    strcat(response, "\n");
    strcat(response, getService(s3));
    strcat(response, "\n");
    return response;
  }

};


class ServiceFactory {

  private:

  Service *service;

  public:
  ServiceFactory(int type){
    printf("ServiceFactory ...");
    if(type == 10){
      service = new SocialService();
    }else if(type == 20){
      service = new ProfessionalService();
    }
  }

  Service* getServiceInstance() {
      return service;
  }

};
