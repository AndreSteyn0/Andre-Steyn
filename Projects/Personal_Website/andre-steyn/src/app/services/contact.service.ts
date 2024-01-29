import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class ContactService {
  private apiUrl =
    'https://4qs8axqlzf.execute-api.af-south-1.amazonaws.com/prod/send-email';
  private apiKey = 'WxUe5mO8k89f5eiLWyT7I379vfz2tBrZ8IqlVKb5';

  constructor(private http: HttpClient) {}

  sendEmail(body: any): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/json',
      'x-api-key': this.apiKey,
    });

    return this.http.post(this.apiUrl, body, { headers });
  }
}
