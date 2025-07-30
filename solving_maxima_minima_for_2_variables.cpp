#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Node{
	int coeffecient;
	int y_exponent;
	int x_exponent;
	struct Node* next;
};
struct Node* create(int c,int x,int y){
	struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
	newnode->coeffecient=c;
	newnode->x_exponent=x;
	newnode->y_exponent=y;
	newnode->next=NULL;
	return newnode;
}
int insert(struct Node** head){
	int c,x,y,n,e;
	struct Node* temp=NULL;
	struct Node* t=NULL;
	printf("\nEnter the number of terms in f(x,y):");
	scanf("%d",&e);
	n=e;
	while(e!=-0){
		printf("\nEnter the coefficient of this term:");
		scanf("%d",&c);
		printf("\nEnter the exponent of x:");
		scanf("%d",&x);
		printf("\nEnter the exponent of y:");
		scanf("%d",&y);
		if (n==e){
			temp=create(c,x,y);
			*head=temp;
			t=temp;
			e--;
		}
		else{
		temp=create(c,x,y);
		t->next=temp;
		t=t->next;
		e--;
		}
	}
}
int display(struct Node* head){
	
	printf("\nF(x,y)=");
	struct Node* temp=head;
	if (temp==NULL){
		printf("0\n");
		return 0;
	}
	while (temp->next!=NULL){
		printf("(%d(x^%d)(y^%d))+",temp->coeffecient,temp->x_exponent,temp->y_exponent);
		temp=temp->next;
	}
	printf("(%d(x^%d)(y^%d))",temp->coeffecient,temp->x_exponent,temp->y_exponent);
}
void maxima(struct Node* head,float max[]){
	struct Node* temp=head;
	float x,y;
	x=max[0];
	y=max[1];
	float val=0;
	while (temp!=NULL){
	val+=temp->coeffecient*pow(x,temp->x_exponent)*pow(y,temp->y_exponent);
	temp=temp->next;
}
	printf("\nThe local maxima of f(x) is =%.4f",val);
}
void minima(struct Node* head,float min[]){
	struct Node* temp=head;
	float x,y;
	x=min[0];
	y=min[1];
	float val=0;
	while (temp!=NULL){
	val+=temp->coeffecient*pow(x,temp->x_exponent)*pow(y,temp->y_exponent);
	temp=temp->next;
}
	printf("\nThe local minima of f(x) is =%.4f",val);
}
void evaluate_points(struct Node** d2x, struct Node** d2y,struct Node** dm,float pts[],float max[],float min[],int *MAX,int *MIN){
	
	for (int i=0;i<10;i+=2){
		float x,y;
		struct Node* L = *d2x;
	    struct Node* N = *d2y;
	    struct Node* M = *dm;
		float l=0.0,m=0.0,n=0.0;
		x=pts[i];
		y=pts[i+1];
		printf("\n\n##new stationary point##\nfor (x,y)=(%.2f,%.2f)\n",x,y);
		while (L!=NULL){
			l+=pow(x,L->x_exponent)*pow(y,L->y_exponent)*L->coeffecient;
			
			L=L->next;
		}
		while (N!=NULL){
			n+=N->coeffecient*pow(x,N->x_exponent)*pow(y,N->y_exponent);
			N=N->next;
		}
		
		while (M!=NULL){
			m+=pow(x,M->x_exponent)*pow(y,M->y_exponent)*M->coeffecient;
			M=M->next;
		}
		printf("\nl=%.4f n=%.4f m=%.4f\n",l,n,m);
		float val1=(l*n);
		float val2=m*m;
		float val= val1-val2;
		printf("\nln-m**2=%.4f\n",val);
		if (val<0.00){
			printf("\n(%.2f,%.2f) is a saddle point.",x,y);
			continue;
		}
		else if(val==0.00){
			printf("\n(%.2f,%.2f) is point with no conclusion.",x,y);
			continue;
		}
		else{
			if (l<0.00){
				printf("\n(%.2f,%.2f) is a point of maxima.",x,y);
				*MAX=1;
				max[0]=x;
				max[1]=y;
			}
			else{
				printf("\n(%.2f,%.2f) is a point of minima.",x,y);
				*MIN=1;
				min[0]=x;
				min[1]=y;
			}
}
	}
}
void finding_stationary_points(struct Node** dx, struct Node** dy,float pts[]) {
    struct Node* temp_dx = *dx;
    struct Node* temp_dy = *dy;
    const char* filename = "derivatives.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        
    }
	if (temp_dx==NULL){
		fprintf(file, "%d",0 );
	}
    while (temp_dx!=NULL){
    if (temp_dx==*dx){
    fprintf(file, "%d*x**%d*y**%d",temp_dx->coeffecient,temp_dx->x_exponent,temp_dx->y_exponent );
    temp_dx=temp_dx->next;
	}
	else if (temp_dx->coeffecient<0){
	fprintf(file, "%d*x**%d*y**%d",temp_dx->coeffecient,temp_dx->x_exponent,temp_dx->y_exponent );
    temp_dx=temp_dx->next;
	}
	else{
	fprintf(file, "+%d*x**%d*y**%d",temp_dx->coeffecient,temp_dx->x_exponent,temp_dx->y_exponent );
    temp_dx=temp_dx->next;
	}
	
}
fprintf(file, "\n");
if (temp_dy==NULL){
		fprintf(file, "%d",0 );
	}
while (temp_dy!=NULL){
    if (temp_dy==*dy){
    fprintf(file, "%d*x**%d*y**%d",temp_dy->coeffecient,temp_dy->x_exponent,temp_dy->y_exponent );
    temp_dy=temp_dy->next;
	}
	else if (temp_dy->coeffecient<0){
	fprintf(file, "%d*x**%d*y**%d",temp_dy->coeffecient,temp_dy->x_exponent,temp_dy->y_exponent  );
    temp_dy=temp_dy->next;
	}
	else{
	fprintf(file, "+%d*x**%d*y**%d",temp_dy->coeffecient,temp_dy->x_exponent,temp_dy->y_exponent  );
    temp_dy=temp_dy->next;
	}
}
    fclose(file);
    printf("\n");
int result = system("py finding_stationary_points.py");

    if (result == 0) {
        printf("\nPython script executed successfully.Stationary points successfully generated.\n");
    } else {
        printf("\nError executing Python script.\n");
    }
	FILE *file2;
    float num;
    const char* file_name = "points.txt";
    file2 = fopen(file_name, "r");
    if (file2 == NULL) {
        printf("Error opening file.\n");
        return;
    }
    int p=1,s=0;
    printf("\nStationary Points are:\n");
    while (fscanf(file2, "%f", &num) != EOF) {
	pts[s]=num;
	if (s%2==0)
	printf("(%.2f,",pts[s]);
	else
	printf("%.2f)\n",pts[s]);
	s++;
    }
    
    fclose(file2);
}


void solve(struct Node* head,struct Node** dx,struct Node** dy,struct Node** d2x,struct Node** d2y,struct Node** m){
	struct Node* temp=head;
	struct Node* temp_dx=*dx;
	struct Node* temp_dy=*dy;
	struct Node* t=NULL;
	int l=0;
	printf("\nLet d denote partial differentiation:\n");
	printf("df/dx=");
	//finding df/dx
	while (temp!=NULL){
		if (temp->x_exponent==0){
		temp=temp->next;
		continue;
}
		int c=temp->x_exponent*temp->coeffecient;
		if (l==0){
			temp_dx=create(c,temp->x_exponent-1,temp->y_exponent);
			*dx=temp_dx;
			t=temp_dx;
			l++;
			temp=temp->next;
		}
		else{
		temp_dx=create(c,temp->x_exponent-1,temp->y_exponent);
		t->next=temp_dx;
		t=temp_dx;
		temp=temp->next;
		}
	}
	temp=head;
	t=NULL;
	l=0;
	display(*dx);
	//finding df/dy
	while (temp!=NULL){
		if (temp->y_exponent==0){
		temp=temp->next;
		continue;
	}
		int c=temp->y_exponent*temp->coeffecient;
		if (l==0){
			temp_dy=create(c,temp->x_exponent,temp->y_exponent-1);
			*dy=temp_dy;
			t=temp_dy;
			l++;
			temp=temp->next;
		}
		else{
		temp_dy=create(c,temp->x_exponent,temp->y_exponent-1);
		t->next=temp_dy;
		t=temp_dy;
		temp=temp->next;
		}
	}
	printf("\ndf/dy=");
	display(*dy);
	struct Node* temp_d2x=*d2x;
	struct Node* temp_d2y=*d2y;
	temp_dx=*dx;
	temp_dy=*dy;
	l=0;
	t=NULL;
	//finding l
	while (temp_dx!=NULL){
		if (temp_dx->x_exponent==0){
		temp_dx=temp_dx->next;
		continue;
	}
		int c=temp_dx->x_exponent*temp_dx->coeffecient;
		if (l==0){
			temp_d2x=create(c,temp_dx->x_exponent-1,temp_dx->y_exponent);
			*d2x=temp_d2x;
			t=temp_d2x;
			l++;
			temp_dx=temp_dx->next;
		}
		else{
		temp_d2x=create(c,temp_dx->x_exponent-1,temp_dx->y_exponent);
		t->next=temp_d2x;
		t=temp_d2x;
		temp_dx=temp_dx->next;
		}
	}
	printf("\nd^2f/dx^2=l=");
	display(*d2x);
	//finding n
	l=0;
	t=NULL;
	while (temp_dy!=NULL){
		if (temp_dy->y_exponent==0){
		temp_dy=temp_dy->next;
		continue;
	}
		int c=temp_dy->y_exponent*temp_dy->coeffecient;
		if (l==0){
			temp_d2y=create(c,temp_dy->x_exponent,temp_dy->y_exponent-1);
			*d2y=temp_d2y;
			t=temp_d2y;
			l++;
			temp_dy=temp_dy->next;
		}
		else{
		temp_d2y=create(c,temp_dy->x_exponent,temp_dy->y_exponent-1);
		t->next=temp_d2y;
		t=temp_d2y;
		temp_dy=temp_dy->next;
		}
	}
	printf("\nd^2f/dy^2=n=");
	display(*d2y);
	//finding m
	struct Node* temp_m=*m;
	temp_dy=*dy;
	l=0;
	t=NULL;
	while (temp_dy!=NULL){
		if (temp_dy->x_exponent==0){
		temp_dy=temp_dy->next;
		continue;
	}
		int c=temp_dy->x_exponent*temp_dy->coeffecient;
		if (l==0){
			temp_m=create(c,temp_dy->x_exponent-1,temp_dy->y_exponent);
			*m=temp_m;
			t=temp_m;
			l++;
			temp_dy=temp_dy->next;
		}
		else{
		temp_m=create(c,temp_dy->x_exponent-1,temp_dy->y_exponent);
		t->next=temp_m;
		t=temp_m;
		temp_dy=temp_dy->next;
		}
	}
	printf("\nd^2f/dxdy=m=");
	display(*m);
}
int main(){
	printf("\nMaxima and Minima Calculator for 2 variable equations without the inclusion of Trigonometric and Logarithmic functions:\n");
 	struct Node* head=NULL;
 	struct Node* dx=NULL;
 	struct Node* dy=NULL;
 	struct Node* d2x=NULL;
 	struct Node* d2y=NULL;
 	struct Node* m=NULL;
	float pts[10];
	float max[2];
	float min[2];
	float root1,root2;
	int MAX=0,MIN=0;
	printf("Enter f(x,y):\n");
	insert(&head);
	display(head);
	solve(head,&dx,&dy,&d2x,&d2y,&m);
	finding_stationary_points(&dx,&dy,pts);
	evaluate_points(&d2x,&d2y,&m,pts,max,min,&MAX,&MIN);
	if (MAX!=0)
	maxima(head,max);
	if (MIN!=0)
	minima(head,min);
	printf("\n");
	system("pause");
}
