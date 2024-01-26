import { Component } from '@angular/core';
import { RouterLink, RouterLinkActive } from '@angular/router';
import { ScrollService } from '../../services/scroll.service';

@Component({
  selector: 'app-header',
  standalone: true,
  imports: [RouterLink, RouterLinkActive],
  templateUrl: './header.component.html',
  styleUrl: './header.component.css',
})
export class HeaderComponent {
  constructor(private scrollService: ScrollService){}

  onClickRedirect(section: string) {
    this.scrollService.scrollTo(section);
  }
}
